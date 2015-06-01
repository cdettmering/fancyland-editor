#include "PlayerGraphicsItem.h"

PlayerGraphicsItem::PlayerGraphicsItem(Player *player, QGraphicsItem *parent)
    : BorderGraphicsPixmapItem(parent),
      _player(player)
{
    if(_player != 0) {
        setPixmap(QPixmap::fromImage(player->getSprite()));
        setPos(_player->getPosition());
    }
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

Player * PlayerGraphicsItem::getPlayer() const
{
    return _player;
}

QVariant PlayerGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //check for position
    if(change == ItemPositionChange) {
        QPointF newPos = value.toPointF();
        //update the player
        if(_player != 0) {
            _player->setPosition(newPos);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
