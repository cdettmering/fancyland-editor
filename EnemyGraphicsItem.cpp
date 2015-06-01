#include "EnemyGraphicsItem.h"

EnemyGraphicsItem::EnemyGraphicsItem(Enemy *enemy, QGraphicsItem *parent)
    : BorderGraphicsPixmapItem(parent)
{
    setEnemy(enemy);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

Enemy * EnemyGraphicsItem::getEnemy() const
{
    return _enemy;
}

void EnemyGraphicsItem::setEnemy(Enemy *enemy)
{
    _enemy = enemy;
    if(_enemy != 0) {
        setPixmap(QPixmap::fromImage(_enemy->getSprite()));
        setPos(_enemy->getPosition());
    }
}

QVariant EnemyGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //check for position
    if(change == ItemPositionChange) {
        QPointF newPos = value.toPointF();
        //update the enemy
        if(_enemy != 0) {
            _enemy->setPosition(newPos);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
