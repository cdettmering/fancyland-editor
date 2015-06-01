#include "Layer.h"

Layer::Layer()
{

}

Layer::Layer(float speed, const QList<Sprite> textures)
    : _speed(speed),
      _textures(textures)
{

}

float Layer::getSpeed() const
{
    return _speed;
}

void Layer::setSpeed(float speed)
{
    _speed = speed;
}

QList<Sprite> Layer::getSprites() const
{
    return _textures;
}

void Layer::setSprites(const QList<Sprite> &textures)
{
    _textures = textures;
}
