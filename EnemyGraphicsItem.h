#ifndef ENEMYGRAPHICSITEM_H
#define ENEMYGRAPHICSITEM_H

#include "datatype/Enemy.h"
#include "BorderGraphicsPixmapItem.h"

#include <QGraphicsPixmapItem>

class EnemyGraphicsItem : public BorderGraphicsPixmapItem
{
public:
    EnemyGraphicsItem(Enemy *enemy, QGraphicsItem *parent = 0);

    Enemy * getEnemy() const;
    void setEnemy(Enemy *enemy);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    Enemy *_enemy;
};

#endif // ENEMYGRAPHICSITEM_H
