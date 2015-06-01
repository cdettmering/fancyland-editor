#include "EditScene.h"
#include "PlayerGraphicsItem.h"
#include "datatype/Enemy.h"
#include "EnemyGraphicsItem.h"

#include <QPainter>
#include <QGraphicsView>
#include <QScrollBar>
#include <QDebug>

EditScene::EditScene(Level *level, QObject *parent)
    : QGraphicsScene(parent),
      _level(0),
      _currentTool(0),
      _player(level->getStartPoint())
{
    setLevel(level);
    initPlayer();
    initEnemies();
}

EditScene::~EditScene()
{
}

Level * EditScene::getLevel() const
{
    return _level;
}

void EditScene::setLevel(Level *level)
{
    _level = level;
    handleLayerChanged();
}

EditTool * EditScene::getTool() const
{
    return _currentTool;
}

void EditScene::setTool(EditTool *tool)
{
    if(_currentTool != 0) {
        qDebug() << "EditScene::setTool - Deactivating " << _currentTool->getDisplayName();
        _currentTool->deactivate();
    }

    _currentTool = tool;

    if(_currentTool != 0) {
        qDebug() << "EditScene::setTool - Activating " << _currentTool->getDisplayName();
        _currentTool->activate(0);
    }
}

void EditScene::handleLayerChanged()
{
    // Figure out which layer is the longest, and set the scene rect to that
    int maxSize = _level->getBackgroundLayer().getSprites().size();
    Layer maxLayer = _level->getBackgroundLayer();
    if(maxSize < _level->getBackForegroundLayer().getSprites().size()) {
        maxSize = _level->getBackForegroundLayer().getSprites().size();
        maxLayer = _level->getBackForegroundLayer();
    }
    if(maxSize < _level->getFunctionalLayer().getSprites().size()) {
        maxSize = _level->getFunctionalLayer().getSprites().size();
        maxLayer = _level->getFunctionalLayer();
    }
    if(maxSize < _level->getForegroundLayer().getSprites().size()) {
        maxSize = _level->getForegroundLayer().getSprites().size();
        maxLayer = _level->getForegroundLayer();
    }

    // Assume each picture in layer is the same size
    if(maxSize > 0) {
        QSize imageFrame = maxLayer.getSprites().at(0).getTexture().size();
        imageFrame.scale(imageFrame.width() * maxSize, imageFrame.height(), Qt::IgnoreAspectRatio);
        QRectF sceneRect(0, 0, imageFrame.width(), imageFrame.height());
        qDebug() << "EditScene::handleLayerChanged - Resizing scene rectangle to " << sceneRect;
        setSceneRect(sceneRect);
    }

    // Redraw backgrond and foreground
    qDebug() << "EditScene::handleLayerChanged - Invalidating background and foreground";
    invalidate(QRectF(), QGraphicsScene::BackgroundLayer | QGraphicsScene::ForegroundLayer);
}

void EditScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(_currentTool != 0) {
        _currentTool->handleMousePress(event);
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void EditScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(_currentTool != 0) {
        _currentTool->handleMouseRelease(event);
    } else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

void EditScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(_currentTool != 0) {
        _currentTool->handleMouseMove(event);
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void EditScene::keyPressEvent(QKeyEvent *event)
{
    if(_currentTool != 0) {
        _currentTool->handleKeyPress(event);
    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void EditScene::keyReleaseEvent(QKeyEvent *event)
{
    if(_currentTool != 0) {
        _currentTool->handleKeyRelease(event);
    } else {
        QGraphicsScene::keyReleaseEvent(event);
    }
}

void EditScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    renderLayer(_level->getBackgroundLayer(), painter, rect);
    renderLayer(_level->getBackForegroundLayer(), painter, rect);
    renderLayer(_level->getFunctionalLayer(), painter, rect);
}

void EditScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    renderLayer(_level->getForegroundLayer(), painter, rect);
}

void EditScene::renderLayer(Layer layer, QPainter *painter, const QRectF &rect)
{
    // Assume all images in the layer are the same size
    //qDebug() << "Rendering layer with " << layer.getSprites().size() << " sprites";
    if(layer.getSprites().size() == 0) {
        return;
    }

    // No views, don't render
    if(views().size() == 0) {
        return;
    }

    QRectF frame = layer.getSprites().at(0).getTexture().rect();

    // Get the left line of the visible area
    qreal visibleX = rect.left();

    // Map to layer coordinates
    qreal x = visibleX * layer.getSpeed();
    int index = (int)(x / frame.width());

    // Get rectangles for frame to the left of index, and to the right
    QRectF targetLeftFrame = frame;
    targetLeftFrame.translate(visibleX + ((index - 1) * frame.width()) - x, 0);

    QRectF targetFrame = frame;
    targetFrame.translate(visibleX + (index * frame.width()) - x, 0);

    QRectF targetRightFrame = frame;
    targetRightFrame.translate(visibleX + ((index + 1) * frame.width()) - x, 0);

    painter->save();

    // Render Left
    if((index - 1) >= 0 && (index - 1) < layer.getSprites().size()) {
        painter->drawImage(targetLeftFrame, layer.getSprites().at(index - 1).getTexture());
    }

    // Render Target
    if(index >= 0 && index < layer.getSprites().size()) {
        painter->drawImage(targetFrame, layer.getSprites().at(index).getTexture());
    }

    // Render Right
    if((index + 1) >= 0 && (index + 1) < layer.getSprites().size()) {
        painter->drawImage(targetRightFrame, layer.getSprites().at(index + 1).getTexture());
    }

    painter->restore();
}

void EditScene::initPlayer()
{
    //add player to scene
    PlayerGraphicsItem *playerGraphics = new PlayerGraphicsItem(&_player);
    addItem(playerGraphics);
}

void EditScene::initEnemies()
{
    //copy enemies out of the level data structure
    QList<QPair<QPointF, Enemy> > enemies = _level->getEnemyMap().getEnemies();
    for(int i = 0; i < enemies.size(); i++) {
        //move enemy to correct location
        Enemy enemy = enemies.at(i).second;
        enemy.setPosition(enemies.at(i).first);

        //put enemy into list
        _enemies.append(enemy);

        //add enemy to scene
        EnemyGraphicsItem *enemyGraphics = new EnemyGraphicsItem(&_enemies[i]);
        addItem(enemyGraphics);
    }
}
