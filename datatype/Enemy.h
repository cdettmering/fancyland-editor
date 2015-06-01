#ifndef ENEMY_H
#define ENEMY_H

#include "Body.h"

#include <QString>
#include <QPointF>
#include <QImage>

class Enemy
{
public:
    Enemy(const QString &type, const QPointF &position, const QString &sprite, const Body &body);

    QString getType() const;
    void setType(const QString &type);

    QPointF getPosition() const;
    void setPosition(const QPointF &position);

    QImage getSprite() const;
    void setSprite(const QImage &sprite);

    Body getBody() const;
    void setBody(const Body &body);
private:
    QString _type;
    QPointF _position;
    QImage _sprite;
    Body _body;
};

#endif // ENEMY_H
