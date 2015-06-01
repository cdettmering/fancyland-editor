#ifndef BODYPART_H
#define BODYPART_H

#include <QPolygonF>
#include <QString>

class BodyPart
{
public:
    BodyPart();

    QString getName() const;
    void setName(const QString &name);

    QPolygonF getShape() const;
    void setShape(const QPolygonF &shape);

private:
    QString _name;
    QPolygonF _shape;
};

#endif // BODYPART_H
