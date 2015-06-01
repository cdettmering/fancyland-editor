#include "DeformJoint.h"
#include "Settings.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

const int DeformJoint::WIDTH = 15;
const int DeformJoint::HEIGHT = 15;

DeformJoint::DeformJoint(QGraphicsItem *parent)
    : QGraphicsRectItem(QRectF(QPointF(), QSize(WIDTH, HEIGHT)), parent)
{
    setTransformOriginPoint(getCenter());
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

DeformJoint::DeformJoint(const QPointF &pos, QGraphicsItem *parent)
    : QGraphicsRectItem(QRectF(pos, QSize(WIDTH, HEIGHT)), parent)
{
    setTransformOriginPoint(getCenter());
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QPointF DeformJoint::getCenter() const
{
    return pos() + rect().center();
}

void DeformJoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->setBrush(Settings::getTerrainAnchorColor());
    painter->setPen(Settings::getTerrainAnchorColor());
    painter->drawRect(rect());

    if(option->state & QStyle::State_Selected) {
        painter->setBrush(Qt::transparent);
        QPen pen = painter->pen();
        pen.setColor(Settings::getItemBorderColor());
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawRect(rect());
    }

    painter->restore();
}
