#include "TerrainFile.h"

QList<QPolygonF> TerrainFile::getPolygons() const
{
    return _polygons;
}

void TerrainFile::setPolygons(const QList<QPolygonF> &polygons)
{
    _polygons = polygons;
}
