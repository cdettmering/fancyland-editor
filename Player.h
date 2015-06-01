#ifndef PLAYER_H
#define PLAYER_H

#include <QImage>
#include <QPointF>

class Player
{
public:
    Player(const QPointF &position);

    QImage getSprite() const;

    QPointF getPosition() const;
    void setPosition(const QPointF &position);
private:
    QImage _sprite;
    QPointF _position;
};

#endif // PLAYER_H
