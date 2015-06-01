#ifndef TERRAIN_H
#define TERRAIN_H

#include <QVector>
#include <QPolygonF>

class Terrain : public QVector<QPolygonF>
{
public:
    Terrain();
    Terrain(int size);
    Terrain(int size, const QPolygonF &other);
    Terrain(const QVector<QPolygonF> &other);
};
#endif // TERRAIN_H
