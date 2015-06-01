#include "Player.h"

Player::Player(const QPointF &position)
    : _sprite("external/FancyLand/textures/player.png"),
      _position(position)

{
}

QImage Player::getSprite() const
{
    return _sprite;
}

QPointF Player::getPosition() const
{
    return _position;
}

void Player::setPosition(const QPointF &position)
{
    _position = position;
}
