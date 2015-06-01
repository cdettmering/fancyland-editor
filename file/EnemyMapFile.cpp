#include "EnemyMapFile.h"

QMap<QString, QString> EnemyMapFile::getDictionary() const
{
    return _dictionary;
}

void EnemyMapFile::setDictionary(const QMap<QString, QString> &dictionary)
{
    _dictionary = dictionary;
}

QList<QPair<QPointF, QString> > EnemyMapFile::getEnemies() const
{
    return _enemies;
}

void EnemyMapFile::setEnemies(const QList<QPair<QPointF, QString> > &enemies)
{
    _enemies = enemies;
}

void EnemyMapFile::setEnemiesFromEnemyList(const QList<QPair<QPointF, Enemy> > &enemies)
{
    QList<QPair<QPointF, QString> > enemyList;
    for(int i = 0; i < enemies.size(); i++) {
        QPair<QPointF, Enemy> currentPair = enemies.at(i);
        enemyList.append(QPair<QPointF, QString>(currentPair.first, currentPair.second.getType()));
    }
    setEnemies(enemyList);
}
