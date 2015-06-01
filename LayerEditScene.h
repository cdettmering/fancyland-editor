#ifndef LAYEREDITSCENE_H
#define LAYEREDITSCENE_H

#include "datatype/Layer.h"

#include <QGraphicsScene>
#include <QSize>
#include <QImage>
#include <QMap>
#include <QPointF>

class LayerEditScene : public QGraphicsScene
{
    Q_OBJECT
public:
    LayerEditScene(Layer *layer = 0, QObject *parent = 0);
    ~LayerEditScene();

    Layer * getLayer() const;
    void setLayer(Layer *layer);

    QSize getPreviewSize() const;
    void setPreviewSize(const QSize &size);

signals:
    void dataChanged();

public slots:
    void handleSpeedChange(float speed);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void recalculatePositions();
    void resizeImages(const QSize &oldSize);
    void insertSprite(int index, const Sprite &sprite, bool previewOnly = false);
    void removeSprite(int index);
    QImage scaleImage(const QImage &image, const QSize &size);
    int mapPointToIndex(const QPointF &point);
    void sync();

    Layer *_layer;
    QVector<QGraphicsPixmapItem *> _previews;
    QMap<QGraphicsPixmapItem *, Sprite> _pixmapToSprite;
    QSize _previewSize;
    QPointF _dragStartPosition;
};

#endif // LAYEREDITSCENE_H
