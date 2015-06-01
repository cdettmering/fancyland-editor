#ifndef TERRAINFILE_H
#define TERRAINFILE_H

#include <QList>
#include <QPolygonF>

class TerrainFile
{
public:
    QList<QPolygonF> getPolygons() const;
    void setPolygons(const QList<QPolygonF> &polygons);

private:
    QList<QPolygonF> _polygons;
};

#endif // TERRAINFILE_H
