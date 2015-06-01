#include "Level.h"

QPointF Level::getStartPoint() const
{
    return _startPoint;
}

void Level::setStartPoint(const QPointF &startPoint)
{
    _startPoint = startPoint;
}

int Level::getFinishLine() const
{
    return _finishLine;
}

void Level::setFinishLine(int finishLine)
{
    _finishLine = finishLine;
}

int Level::getTimeToComplete() const
{
    return _timeToComplete;
}

void Level::setTimeToComplete(int timeToComplete)
{
    _timeToComplete = timeToComplete;
}

EnemyMap Level::getEnemyMap() const
{
    return _enemyMap;
}

void Level::setEnemyMap(const EnemyMap &enemyMap)
{
    _enemyMap = enemyMap;
}

Terrain Level::getTerrain() const
{
    return _terrain;
}

void Level::setTerrain(const Terrain &terrain)
{
    _terrain = terrain;
}

Layer Level::getBackgroundLayer() const
{
    return _backgroundLayer;
}

void Level::setBackgroundLayer(const Layer &backgroundLayer)
{
    _backgroundLayer = backgroundLayer;
}

Layer Level::getBackForegroundLayer() const
{
    return _backForegroundLayer;
}

void Level::setBackForegroundLayer(const Layer &backForegroundLayer)
{
    _backForegroundLayer = backForegroundLayer;
}

Layer Level::getFunctionalLayer() const
{
    return _functionalLayer;
}

void Level::setFunctionalLayer(const Layer &functionalLayer)
{
    _functionalLayer = functionalLayer;
}

Layer Level::getForegroundLayer() const
{
    return _foregroundLayer;
}

void Level::setForegroundLayer(const Layer &foregroundLayer)
{
    _foregroundLayer = foregroundLayer;
}
