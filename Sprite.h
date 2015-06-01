#ifndef SPRITE_H
#define SPRITE_H

#include <QImage>
#include <QString>
#include <QFileInfo>

class Sprite
{
public:
    Sprite();
    Sprite(const QImage &image, const QString &filename);

    bool operator==(const Sprite &other) const;
    bool operator!=(const Sprite &other) const;

    QImage getTexture() const;
    void setTexture(const QImage &image);

    QFileInfo getFileInfo() const;
    void setFilename(const QFileInfo &info);

private:
    QImage _image;
    QFileInfo _info;
};

#endif // SPRITE_H
