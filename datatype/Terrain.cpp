#include "Terrain.h"

Terrain::Terrain()
    : QVector<QPolygonF>()
{

}

Terrain::Terrain(int size)
    : QVector<QPolygonF>(size)
{

}

Terrain::Terrain(int size, const QPolygonF &other)
    : QVector<QPolygonF>(size, other)
{

}

Terrain::Terrain(const QVector<QPolygonF> &other)
    : QVector<QPolygonF>(other)
{

}
