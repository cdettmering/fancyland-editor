#ifndef LAYERFILE_H
#define LAYERFILE_H

#include "Sprite.h"

#include <QStringList>

class LayerFile
{
public:
    float getSpeed() const;
    void setSpeed(float speed);

    QStringList getTextures() const;
    void setTextures(const QStringList &textures);

    void setTexturesFromSpriteList(const QList<Sprite> &sprites);

private:
    float _speed;
    QStringList _textures;
};

#endif // LAYERFILE_H
