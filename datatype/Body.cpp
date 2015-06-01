#include "Body.h"

Body::Body()
    : QVector<BodyPart>()
{
}

Body::Body(const QVector<BodyPart> &other)
    : QVector<BodyPart>(other)
{

}

Body::Body(int size)
    : QVector<BodyPart>(size)
{

}

Body::Body(int size, const BodyPart &other)
    : QVector<BodyPart>(size, other)
{

}

QString Body::getType() const
{
    return _type;
}

void Body::setType(const QString &type)
{
    _type = type;
}
