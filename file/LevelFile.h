#ifndef LEVELFILE_H
#define LEVELFILE_H

#include <QPointF>
#include <QString>

class LevelFile
{
public:
    QPointF getStartPoint() const;
    void setStartPoint(const QPointF &startPoint);

    int getFinishLine() const;
    void setFinishLine(int finishLine);

    int getTimeToComplete() const;
    void setTimeToComplete(int timeToComplete);

    QString getEnemyMapFile() const;
    void setEnemyMapFile(const QString &enemyMapFile);

    QString getTerrainFile() const;
    void setTerrainFile(const QString &terrainFile);

    QString getBackgroundLayerFile() const;
    void setBackgroundLayerFile(const QString &backgroundLayerFile);

    QString getBackForegroundLayerFile() const;
    void setBackForegroundLayerFile(const QString &backForegroundLayerFile);

    QString getFunctionalLayerFile() const;
    void setFunctionalLayerFile(const QString &functionalLayerFile);

    QString getForegroundLayerFile() const;
    void setForegroundLayerFile(const QString &foregroundLayerFile);

private:
    QPointF _startPoint;
    int _finishLine;
    int _timeToComplete;
    QString _enemyMapFile;
    QString _terrainFile;
    QString _backgroundLayerFile;
    QString _backForegroundLayerFile;
    QString _functionalLayerFile;
    QString _foregroundLayerFile;
};

#endif // LEVELFILE_H
