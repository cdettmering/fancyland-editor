#ifndef PLAYERGRAPHICSITEM_H
#define PLAYERGRAPHICSITEM_H

#include "Player.h"
#include "BorderGraphicsPixmapItem.h"

#include <QGraphicsPixmapItem>

class PlayerGraphicsItem : public BorderGraphicsPixmapItem
{
public:
    PlayerGraphicsItem(Player *player, QGraphicsItem *parent = 0);

    Player * getPlayer() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    Player *_player;
};

#endif // PLAYERGRAPHICSITEM_H
