#ifndef LAYER_H
#define LAYER_H

#include "../Sprite.h"

#include <QList>
#include <QImage>

class Layer
{
public:
    Layer();
    Layer(float speed, const QList<Sprite> textures);

    float getSpeed() const;
    void setSpeed(float speed);

    QList<Sprite> getSprites() const;
    void setSprites(const QList<Sprite> &textures);
private:
    float _speed;
    QList<Sprite> _textures;
};

#endif // LAYER_H
