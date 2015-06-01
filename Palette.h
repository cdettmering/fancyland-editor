#ifndef PALETTE_H
#define PALETTE_H

#include "Sprite.h"

#include <QGraphicsScene>
#include <QList>
#include <QImage>
#include <QMap>

class Palette : public QGraphicsScene
{
public:
    Palette(QObject *parent = 0);
    ~Palette();

    int getNumberOfColumns() const;
    void setNumberOfColumns(int columns);

    QSize getPreviewSize() const;
    void setPreviewSize(const QSize &size);

    bool isGridVisible() const;
    void setGridVisible(bool visible);

    QList<Sprite> getSprites() const;
    void setSprites(const QList<Sprite> &sprites);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


private:
    void recalculatePositions();
    void resizeImages(const QSize &oldSize, const QSize &newSize);
    QList<Sprite> sortBySize(const QList<Sprite> &sprites);
    QList<Sprite> _sprites;
    QList<QGraphicsPixmapItem *> _previews;
    QMap<QGraphicsPixmapItem *, Sprite> _pixmapToSprite;
    QSize _previewSize;
    int _numberOfColumns;
    bool _gridVisible;
    QPointF _dragStartPosition;
};

#endif // PALETTE_H
