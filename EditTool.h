#ifndef EDITTOOL_H
#define EDITTOOL_H

#include "datatype/Level.h"

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QWidget>

class EditScene;

class EditTool : public QObject
{
    Q_OBJECT
public:
    EditTool(EditScene *editScene, QObject *parent = 0);

    virtual QString getDisplayName() const  = 0;
    virtual QList<QAction *> getActions() const = 0;
    virtual void activate(QWidget *personalSpace = 0) = 0;
    virtual void deactivate() = 0;
    virtual void sync(Level *level) = 0;
    virtual void handleMousePress(QGraphicsSceneMouseEvent *event) = 0;
    virtual void handleMouseRelease(QGraphicsSceneMouseEvent *event) = 0;
    virtual void handleMouseMove(QGraphicsSceneMouseEvent *event) = 0;
    virtual void handleKeyPress(QKeyEvent *keyEvent) = 0;
    virtual void handleKeyRelease(QKeyEvent *keyEvent) = 0;
protected:
    EditScene *_editScene;
};

#endif // EDITTOOL_H
