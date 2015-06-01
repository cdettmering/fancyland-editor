#ifndef ENEMYFILE_H
#define ENEMYFILE_H

#include "datatype/Body.h"

#include <QString>

class EnemyFile
{
public:
    QString getType() const;
    void setType(const QString &type);

    QString getSpriteFile() const;
    void setSpriteFile(const QString &spriteFile);

    Body getBody() const;
    void setBody(const Body &body);

private:
    QString _type;
    QString _spriteFile;
    Body _body;
};

#endif // ENEMYFILE_H
