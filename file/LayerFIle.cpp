#include "LayerFile.h"

float LayerFile::getSpeed() const
{
    return _speed;
}

void LayerFile::setSpeed(float speed)
{
    _speed = speed;
}

QStringList LayerFile::getTextures() const
{
    return _textures;
}

void LayerFile::setTextures(const QStringList& textures)
{
    _textures = textures;
}

void LayerFile::setTexturesFromSpriteList(const QList<Sprite> &sprites)
{
    QStringList textures;
    for(int i = 0; i < sprites.size(); i++) {
        textures.append(sprites.at(i).getFileInfo().fileName());
    }
    setTextures(textures);
}
