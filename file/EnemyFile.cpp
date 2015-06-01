#include "EnemyFile.h"

QString EnemyFile::getType() const
{
    return _type;
}

void EnemyFile::setType(const QString &type)
{
    _type = type;
}

QString EnemyFile::getSpriteFile() const
{
    return _spriteFile;
}

void EnemyFile::setSpriteFile(const QString &spriteFile)
{
    _spriteFile = spriteFile;
}

Body EnemyFile::getBody() const
{
    return _body;
}

void EnemyFile::setBody(const Body &body)
{
    _body = body;
}
