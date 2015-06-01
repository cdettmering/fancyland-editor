#ifndef EDITSCENE_H
#define EDITSCENE_H

#include "datatype/Level.h"
#include "EditTool.h"
#include "Player.h"

#include <QGraphicsScene>

class EditScene : public QGraphicsScene
{
    Q_OBJECT
public:
    EditScene(Level *level, QObject *parent = 0);
    ~EditScene();

    Level * getLevel() const;
    void setLevel(Level *level);

    EditTool * getTool() const;
    void setTool(EditTool *tool);

public slots:
    void handleLayerChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);

private:
    void renderLayer(Layer layer, QPainter *painter, const QRectF &rect);
    void initPlayer();
    void initEnemies();
    Level *_level;
    EditTool *_currentTool;
    Player _player;
    QList<Enemy> _enemies;
};

#endif // EDITSCENE_H
