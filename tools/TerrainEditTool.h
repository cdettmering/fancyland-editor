#ifndef TERRAINEDITTOOL_H
#define TERRAINEDITTOOL_H

#include "EditTool.h"
#include "DeformableGraphicsItem.h"
#include "datatype/Terrain.h"

#include <QVector>
#include <QPolygonF>

class TerrainEditTool : public EditTool
{
    Q_OBJECT
public:
    TerrainEditTool(EditScene *editScene, QObject *parent = 0);

    QString getDisplayName() const;
    QList<QAction *> getActions() const;
    void activate(QWidget *personalSpace);
    void deactivate();
    void sync(Level *level);
    void handleMousePress(QGraphicsSceneMouseEvent *event);
    void handleMouseRelease(QGraphicsSceneMouseEvent *event);
    void handleMouseMove(QGraphicsSceneMouseEvent *event);
    void handleKeyPress(QKeyEvent *keyEvent);
    void handleKeyRelease(QKeyEvent *keyEvent);

private slots:
    void startNewPolygon();

private:
    void addItem(DeformableGraphicsItem *item);
    void finalizeItem();
    void initTerrain(Terrain terrain);
    static const QString DISPLAY_NAME;
    QList<QAction *> _actions;
    QList<DeformableGraphicsItem *> _items;
    DeformableGraphicsItem *_item;
};

#endif // TERRAINEDITTOOL_H
