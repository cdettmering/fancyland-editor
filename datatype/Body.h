#ifndef BODY_H
#define BODY_H

#include "BodyPart.h"

#include <QVector>
#include <QString>

class Body : public QVector<BodyPart>
{
public:
    Body();
    Body(int size);
    Body(int size, const BodyPart &other);
    Body(const QVector<BodyPart> &other);

    QString getType() const;
    void setType(const QString &type);

private:
    QString _type;
};
#endif // BODY_H
