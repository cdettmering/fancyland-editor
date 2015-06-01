#ifndef ENEMYMAPFILE_H
#define ENEMYMAPFILE_H

#include "datatype/Enemy.h"

#include <QMap>
#include <QList>
#include <QPair>
#include <QPointF>
#include <QString>

class EnemyMapFile
{
public:
    QMap<QString, QString> getDictionary() const;
    void setDictionary(const QMap<QString, QString> &dictionary);

    QList<QPair<QPointF, QString> > getEnemies() const;
    void setEnemies(const QList<QPair<QPointF, QString> > &enemies);

    void setEnemiesFromEnemyList(const QList<QPair<QPointF, Enemy> > &enemies);

private:
    QMap<QString, QString> _dictionary;
    QList<QPair<QPointF, QString> > _enemies;
};

#endif // ENEMYMAPFILE_H
