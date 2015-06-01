#ifndef LEVEL_H
#define LEVEL_H

#include "EnemyMap.h"
#include "Layer.h"
#include "Terrain.h"

#include <QPointF>
#include <QVector>
#include <QPolygonF>

class Level
{
public:
    QPointF getStartPoint() const;
    void setStartPoint(const QPointF &startPoint);

    int getFinishLine() const;
    void setFinishLine(int finishLine);

    int getTimeToComplete() const;
    void setTimeToComplete(int timeToComplete);

    EnemyMap getEnemyMap() const;
    void setEnemyMap(const EnemyMap& enemyMap);

    Terrain getTerrain() const;
    void setTerrain(const Terrain &terrain);

    Layer getBackgroundLayer() const;
    void setBackgroundLayer(const Layer& backgroundLayer);

    Layer getBackForegroundLayer() const;
    void setBackForegroundLayer(const Layer& backForegroundLayer);

    Layer getFunctionalLayer() const;
    void setFunctionalLayer(const Layer& functionalLayer);

    Layer getForegroundLayer() const;
    void setForegroundLayer(const Layer& foregroundLayer);
private:
    QPointF _startPoint;
    int _finishLine;
    int _timeToComplete;
    EnemyMap _enemyMap;
    Terrain _terrain;
    Layer _backgroundLayer;
    Layer _backForegroundLayer;
    Layer _functionalLayer;
    Layer _foregroundLayer;
};

#endif // LEVEL_H
