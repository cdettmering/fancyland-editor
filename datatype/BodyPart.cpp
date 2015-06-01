#include "BodyPart.h"

BodyPart::BodyPart()
{

}

QString BodyPart::getName() const
{
    return _name;
}

void BodyPart::setName(const QString &name)
{
    _name = name;
}

QPolygonF BodyPart::getShape() const
{
    return _shape;
}

void BodyPart::setShape(const QPolygonF &shape)
{
    _shape = shape;
}
