#include "LayerEditScene.h"
#include "BorderGraphicsPixmapItem.h"

#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QKeyEvent>
#include <QDebug>

LayerEditScene::LayerEditScene(Layer *layer, QObject *parent)
    : QGraphicsScene(parent),
      _layer(layer),
      _previewSize(228, 128)
{
    setLayer(_layer);
}

LayerEditScene::~LayerEditScene()
{

}

Layer * LayerEditScene::getLayer() const
{
    return _layer;
}

void LayerEditScene::setLayer(Layer *layer)
{
    _layer = layer;
    if(_layer != 0) {
        resizeImages(QSize());
        recalculatePositions();
    }
}

void LayerEditScene::handleSpeedChange(float speed)
{
    _layer->setSpeed(speed);
}

void LayerEditScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void LayerEditScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void LayerEditScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "LayerEditScene::dropEvent - Receiving drop event";
    // Make sure the drop is a sprite
    if(event->mimeData()->hasImage() && event->mimeData()->hasText()) {
        QString filename = event->mimeData()->text();
        QImage image = event->mimeData()->imageData().value<QImage>();

        // Make a sprite
        Sprite sprite(image, filename);

        // Insert sprite into scene
        int index = mapPointToIndex(event->scenePos());
        insertSprite(index, sprite);
        recalculatePositions();

        event->acceptProposedAction();
    } else {
        qDebug() << "LayerEditScene::dropEvent - Mime data does not contain image AND text, ignoring.";
        event->ignore();
    }
}

void LayerEditScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        _dragStartPosition = event->scenePos();
    }
    QGraphicsScene::mousePressEvent(event);
}

void LayerEditScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!event->buttons() & Qt::LeftButton) {
        return;
    }

    if((event->scenePos() - _dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }

    qDebug() << "LayerEditScene::mouseMoveEvent - Starting a drag";

    // Get the pixmap item related to the start of the drag.
    QGraphicsItem *item = itemAt(_dragStartPosition, QTransform());
    if(item == 0) {
        // Couldn't find an item at the location for some reason.
        qDebug() << "LayerEditScene::mouseMoveEvent - Could not find a sprite at the drag location.";
        return;
    }

    // Static cast is safe because this scene only adds QGraphicsPixmapItem
    QGraphicsPixmapItem *pixmapItem = static_cast<QGraphicsPixmapItem *>(item);

    // Remove item from scene
    Sprite sprite = _pixmapToSprite[pixmapItem]; // Save sprite before it's removed.
    qDebug() << "LayerEditScene::mouseMoveEvent - Dragging " << sprite.getFileInfo().fileName();

    int index = _previews.indexOf(pixmapItem);
    if(index != -1) {
        removeSprite(index);
        recalculatePositions();
    }

    // Create a new drag event and put the source image into the mime data.
    QDrag *drag = new QDrag((QObject *)event->widget());
    QMimeData *data = new QMimeData();
    data->setImageData(sprite.getTexture());
    data->setText(sprite.getFileInfo().absoluteFilePath());
    drag->setMimeData(data);

    // Put the pixmap that was selected onto the cursor
    QPixmap pixmap = pixmapItem->pixmap();
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));

    // Execute the drag with a move action.
    qDebug() << "LayerEditScene::mouseMoveEvent - Executing drag as MoveAction";
    Qt::DropAction action = drag->exec(Qt::MoveAction, Qt::MoveAction);

    if(action != Qt::MoveAction) {
        // Put sprite back
        qDebug() << "LayerEditScene::mouseMoveEvent - Move action failed, putting sprite back where it was.";
        insertSprite(index, sprite);
        recalculatePositions();
    } else {
        // Delete the old item
        qDebug() << "LayerEditScene::mouseMoveEvent - Move succeeded, deleting old sprite.";
        delete pixmapItem;
    }
}

void LayerEditScene::keyPressEvent(QKeyEvent *event)
{
    // Remove all selected items when the delete key is pressed.
    if(event->key() == Qt::Key_Delete) {
        QList<QGraphicsPixmapItem *> remove;
        for(int i = 0; i < items().size(); i++) {
            if(items().at(i)->isSelected()) {
                remove.append(static_cast<QGraphicsPixmapItem *>(items().at(i)));
            }
        }
        for(int i = 0; i < remove.size(); i++) {
            removeSprite(_previews.indexOf(remove.at(i)));
            recalculatePositions();
        }
    }
}

void LayerEditScene::recalculatePositions()
{
    for(int i = 0; i < _previews.size(); i++) {
        _previews.at(i)->setPos(QPointF(i * _previewSize.width(), 0));
    }
}

void LayerEditScene::resizeImages(const QSize &oldSize)
{
    if(oldSize != _previewSize) {
        for(int i = 0; i < _previews.size(); i++) {
            removeItem(_previews.at(i));
            delete _previews[i];
        }
        _previews.clear();
        _pixmapToSprite.clear();

        int size = _layer->getSprites().size();
        for(int i = 0; i < size; i++) {
            insertSprite(_previews.size(), _layer->getSprites().at(i), true);
        }
    }
}

void LayerEditScene::insertSprite(int index, const Sprite &sprite, bool previewOnly)
{
    qDebug() << "LayerEditScene::insertSprite - Inserting sprite to index " << index << " Preview only " << previewOnly;

    if(!previewOnly) {
        // Add to layer
        QList<Sprite> sprites = _layer->getSprites();
        sprites.insert(index, sprite);
        _layer->setSprites(sprites);
    }

    // Resize to preview size
    qDebug() << "LayerEditScene::insertSprite - Resizing sprite to " << _previewSize;
    QImage sizedImage = scaleImage(sprite.getTexture(), _previewSize);

    // insert into scene
    QGraphicsPixmapItem *pixmap = new BorderGraphicsPixmapItem(QPixmap::fromImage(sizedImage));
    addItem(pixmap);
    pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
    _pixmapToSprite.insert(pixmap, sprite);
    _previews.insert(index, pixmap);
    emit dataChanged();
}

void LayerEditScene::removeSprite(int index)
{
    qDebug() << "LayerEditScene::removeSprite - Removing sprite from index " << index;

    // Remove from layer
    QList<Sprite> sprites = _layer->getSprites();
    sprites.removeAt(index);
    _layer->setSprites(sprites);


    // Remove from scene
    QGraphicsPixmapItem *item = _previews.at(index);
    removeItem(item);
    _previews.remove(index);
    _pixmapToSprite.remove(item);
    emit dataChanged();
}

QImage LayerEditScene::scaleImage(const QImage &image, const QSize &size)
{
    return image.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

int LayerEditScene::mapPointToIndex(const QPointF &point)
{
    int x = point.x();
    x /=  _previewSize.width();

    // Clip to range
    x = qMax(0, x);
    x = qMin(x, _previews.size());

    return x;
}
