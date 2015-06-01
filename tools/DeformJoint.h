#ifndef DEFORMJOINT_H
#define DEFORMJOINT_H

#include <QGraphicsRectItem>

class DeformJoint : public QGraphicsRectItem
{
public:
    DeformJoint(QGraphicsItem *parent = 0);
    DeformJoint(const QPointF &pos, QGraphicsItem *parent = 0);

    QPointF getCenter() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    static const int WIDTH;
    static const int HEIGHT;
};

#endif // DEFORMJOINT_H
