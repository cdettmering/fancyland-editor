#include "DeformableGraphicsItem.h"
#include "Settings.h"

#include <QPainter>
#include <QEvent>
#include <QDebug>

DeformableGraphicsItem::DeformableGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFiltersChildEvents(true);
}

DeformableGraphicsItem::~DeformableGraphicsItem()
{

}

void DeformableGraphicsItem::addJoint(const QPointF &pos)
{
    qDebug() << "DeformableGraphicsItem::addJoint - Adding joint at " << pos;
    prepareGeometryChange();
    DeformJoint *joint = new DeformJoint(pos, this);
    _joints.append(joint);
}

QList<DeformJoint *> DeformableGraphicsItem::getJoints() const
{
    return _joints.toList();
}

QPolygonF DeformableGraphicsItem::getPolygon() const
{
    QPolygonF polygon;
    for(int i = 0; i < _joints.size(); i++) {
        polygon.append(_joints.at(i)->getCenter());
    }
    return polygon;
}

QRectF DeformableGraphicsItem::boundingRect() const
{
    qDebug() << "DeformableGraphicsItem::boundingRect - Calculating bounding box";
    if(_joints.size() == 0) {
        return QRectF();
    }

    // Bounding boxes are given in item coordinates, so translate the bounding box into scene coordinates.
    QRectF seedBB = _joints.at(0)->boundingRect();
    seedBB.translate(_joints.at(0)->pos());
    qreal minX = seedBB.left();
    qreal minY = seedBB.top();
    qreal maxY = seedBB.bottom();
    qreal maxX = seedBB.right();

    for(int i = 0; i < _joints.size(); i++) {
        QRectF bb = _joints.at(i)->boundingRect();
        bb.translate(_joints.at(i)->pos());
        if(bb.left() < minX) {
            minX = bb.left();
        }
        if(bb.right() > maxX) {
            maxX = bb.right();
        }
        if(bb.top() < minY) {
            minY = bb.top();
        }
        if(bb.bottom() > maxY) {
            maxY = bb.bottom();
        }
    }

    return QRectF(QPointF(minX, minY), QSizeF(maxX - minX, maxY - minY));
}

void DeformableGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(_joints.size() > 1) {
        painter->save();
        painter->setBrush(Settings::getTerrainLineColor());
        painter->setPen(Settings::getTerrainLineColor());
       for(int i = 0; i < _joints.size() - 1; i++) {
            QPointF start = _joints.at(i)->getCenter();
            QPointF end = _joints.at(i + 1)->getCenter();
            painter->drawLine(start, end);
        }
        //connect the last 2 points
        QPointF start = _joints.first()->getCenter();
        QPointF end = _joints.last()->getCenter();
        painter->drawLine(start, end);
        //painter->drawRect(boundingRect());
        painter->restore();
    }
}

bool DeformableGraphicsItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneDragMove ||
       event->type() == QEvent::GraphicsSceneMouseMove) {
        // Change geometry if any children are being moved.
        // The DeformableGraphicsItem does not want to handle the actual move, just prepare for it.
        qDebug() << "DeformableGraphicsItem::sceneEventFilter - Child move detected, preparing geometry change";
        prepareGeometryChange();
    }
    // Let Qt handle the rest of the event as usual.
    return false;
}
