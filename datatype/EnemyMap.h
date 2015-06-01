#ifndef ENEMYMAP_H
#define ENEMYMAP_H

#include "Enemy.h"
#include "file/EnemyMapFile.h"

#include <QList>
#include <QMap>
#include <QString>
#include <QPointF>
#include <QPair>

class EnemyMap
{
public:
    EnemyMap();
    EnemyMap(const QMap<QString, QString> &dictionary, const QList<QPair<QPointF, Enemy> > &enemies);

    QMap<QString, QString> getDictionary() const;
    void setDictionary(const QMap<QString, QString> &dictionary);

    QList<QPair<QPointF, Enemy> > getEnemies() const;
    void setEnemies(const QList<QPair<QPointF, Enemy> > enemies);
private:
    QMap<QString, QString> _dictionary;
    QList<QPair<QPointF, Enemy> > _enemies;
};

#endif // ENEMYMAP_H
