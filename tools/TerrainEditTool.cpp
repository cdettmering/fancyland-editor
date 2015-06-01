#include "TerrainEditTool.h"
#include "../EditScene.h"

#include <QAction>
#include <QDebug>

const QString TerrainEditTool::DISPLAY_NAME = "Terrain Tool";

TerrainEditTool::TerrainEditTool(EditScene *editScene, QObject *parent)
    : EditTool(editScene, parent),
      _item(0)
{
    QAction *newPolygonAction = new QAction(this);
    newPolygonAction->setText(tr("New Polygon"));
    connect(newPolygonAction, SIGNAL(triggered()), this, SLOT(startNewPolygon()));
    _actions.append(newPolygonAction);
    initTerrain(editScene->getLevel()->getTerrain());
}

QString TerrainEditTool::getDisplayName() const
{
    return tr(DISPLAY_NAME.toStdString().c_str());
}

QList<QAction *> TerrainEditTool::getActions() const
{
    return _actions;
}

void TerrainEditTool::activate(QWidget *personalSpace)
{
    qDebug() << "TerrainEditTool::activate - Activating";
}

void TerrainEditTool::deactivate()
{
    qDebug() << "TerrainEditTool::deactivate - Deactivating";
    finalizeItem();
}

void TerrainEditTool::sync(Level *level)
{
    // Generate Terrain object
    Terrain terrain;
    for(int i = 0; i < _items.size(); i++) {
        terrain.append(_items.at(i)->getPolygon());
    }
    level->setTerrain(terrain);
}

void TerrainEditTool::handleMousePress(QGraphicsSceneMouseEvent *event)
{
    if(_item == 0) {
        startNewPolygon();
    }
    qDebug() << "TerrainEditTool::handleMousePress - Adding DeformJoint at " << event->scenePos();
    _item->addJoint(event->scenePos());
}

void TerrainEditTool::handleMouseRelease(QGraphicsSceneMouseEvent *event)
{

}

void TerrainEditTool::handleMouseMove(QGraphicsSceneMouseEvent *event)
{

}

void TerrainEditTool::handleKeyPress(QKeyEvent *keyEvent)
{

}

void TerrainEditTool::handleKeyRelease(QKeyEvent *keyEvent)
{

}

void TerrainEditTool::startNewPolygon()
{
    finalizeItem();
    qDebug() << "TerrainEditTool::startNewPolygon - Starting new polygon";
    _item = new DeformableGraphicsItem();
    _editScene->addItem(_item);

}

void TerrainEditTool::finalizeItem()
{
    if(_item != 0) {
        if(_item->getJoints().size() < 3) {
            _editScene->removeItem(_item);
        } else {
            _items.append(_item);
        }
        _item = 0;
    }
}

void TerrainEditTool::initTerrain(Terrain terrain)
{
    for(int polygonIndex = 0; polygonIndex < terrain.size(); polygonIndex++) {
        QPolygonF polygon = terrain.at(polygonIndex);
        if(polygon.size() >= 3) {
            DeformableGraphicsItem *item = new DeformableGraphicsItem();
            _editScene->addItem(item);
            _items.append(item);
            for(int vertexIndex = 0; vertexIndex < polygon.size(); vertexIndex++) {
                qDebug() << vertexIndex;
                QPointF vertex = polygon.at(vertexIndex);
                item->addJoint(vertex);
            }
        } else {
            qDebug() << "TerrainEditTool::initTerrain - Invalid polygon found in terrain, less than 3 vertices.";
        }
    }
}
