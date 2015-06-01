#include "LevelFile.h"

QPointF LevelFile::getStartPoint() const
{
    return _startPoint;
}

void LevelFile::setStartPoint(const QPointF &startPoint)
{
    _startPoint = startPoint;
}

int LevelFile::getFinishLine() const
{
    return _finishLine;
}

void LevelFile::setFinishLine(int finishLine)
{
    _finishLine = finishLine;
}

int LevelFile::getTimeToComplete() const
{
    return _timeToComplete;
}

void LevelFile::setTimeToComplete(int timeToComplete)
{
    _timeToComplete = timeToComplete;
}

QString LevelFile::getEnemyMapFile() const
{
    return _enemyMapFile;
}

void LevelFile::setEnemyMapFile(const QString &enemyMapFile)
{
    _enemyMapFile = enemyMapFile;
}

QString LevelFile::getTerrainFile() const
{
    return _terrainFile;
}

void LevelFile::setTerrainFile(const QString &terrainFile)
{
    _terrainFile = terrainFile;
}

QString LevelFile::getBackgroundLayerFile() const
{
    return _backgroundLayerFile;
}

void LevelFile::setBackgroundLayerFile(const QString &backgroundLayerFile)
{
    _backgroundLayerFile = backgroundLayerFile;
}

QString LevelFile::getBackForegroundLayerFile() const
{
    return _backForegroundLayerFile;
}

void LevelFile::setBackForegroundLayerFile(const QString &backForegroundLayerFile)
{
    _backForegroundLayerFile = backForegroundLayerFile;
}

QString LevelFile::getFunctionalLayerFile() const
{
    return _functionalLayerFile;
}

void LevelFile::setFunctionalLayerFile(const QString &functionalLayerFile)
{
    _functionalLayerFile = functionalLayerFile;
}

QString LevelFile::getForegroundLayerFile() const
{
    return _foregroundLayerFile;
}

void LevelFile::setForegroundLayerFile(const QString &foregroundLayerFile)
{
    _foregroundLayerFile = foregroundLayerFile;
}
