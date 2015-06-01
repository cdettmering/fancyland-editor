#ifndef IMPORTMENU_H
#define IMPORTMENU_H

#include "Workspace.h"

#include <QObject>

class ImportMenu : public QObject
{
    Q_OBJECT
public:
    ImportMenu(Workspace *ws, QObject *parent = 0);

signals:
    void spritesChanged(const QList<Sprite> &sprites);

public slots:
    void importSprites();
    void importEnemies();

private:
    Workspace *_ws;
};

#endif // IMPORTMENU_H
