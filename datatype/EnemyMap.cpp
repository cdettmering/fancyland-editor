#include "EnemyMap.h"

EnemyMap::EnemyMap()
{

}

EnemyMap::EnemyMap(const QMap<QString, QString> &dictionary, const QList<QPair<QPointF, Enemy> > &enemies)
    : _dictionary(dictionary),
      _enemies(enemies)
{

}

QMap<QString, QString> EnemyMap::getDictionary() const
{
    return _dictionary;
}

void EnemyMap::setDictionary(const QMap<QString, QString> &dictionary)
{
    _dictionary = dictionary;
}

QList<QPair<QPointF, Enemy> > EnemyMap::getEnemies() const
{
    return _enemies;
}

void EnemyMap::setEnemies(const QList<QPair<QPointF, Enemy> > enemies)
{
    _enemies = enemies;
}
