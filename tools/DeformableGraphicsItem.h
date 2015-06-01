#ifndef DEFORMABLEGRAPHICSITEM_H
#define DEFORMABLEGRAPHICSITEM_H

#include "DeformJoint.h"

#include <QGraphicsItem>
#include <QList>
#include <QPolygonF>

class DeformableGraphicsItem : public QGraphicsItem
{
public:
    DeformableGraphicsItem(QGraphicsItem *parent = 0);
    ~DeformableGraphicsItem();

    void addJoint(const QPointF &pos);
    QList<DeformJoint *> getJoints() const;
    QPolygonF getPolygon() const;

    QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

private:
    QVector<DeformJoint *> _joints;
};

#endif // DEFORMABLEGRAPHICSITEM_H
