#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(const QImage &image, const QString &filename)
    : _image(image),
      _info(filename)
{

}

bool Sprite::operator==(const Sprite &other) const
{
    return (_image == other._image && _info == other._info);
}

bool Sprite::operator!=(const Sprite &other) const
{
    return !(*this == other);
}

QImage Sprite::getTexture() const
{
    return _image;
}

void Sprite::setTexture(const QImage &image)
{
    _image = image;
}

QFileInfo Sprite::getFileInfo() const
{
    return _info;
}

void Sprite::setFilename(const QFileInfo &info)
{
    _info = info;
}
