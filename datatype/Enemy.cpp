#include "Enemy.h"

Enemy::Enemy(const QString &type, const QPointF &position, const QString &sprite, const Body &body)
    : _type(type),
      _position(position),
      _sprite(sprite),
      _body(body)
{

}

QString Enemy::getType() const
{
    return _type;
}

void Enemy::setType(const QString &type)
{
    _type = type;
}

QPointF Enemy::getPosition() const
{
    return _position;
}

void Enemy::setPosition(const QPointF &position)
{
    _position = position;
}

QImage Enemy::getSprite() const
{
    return _sprite;
}

void Enemy::setSprite(const QImage &sprite)
{
    _sprite = sprite;
}

Body Enemy::getBody() const
{
    return _body;
}

void Enemy::setBody(const Body &body)
{
    _body = body;
}
