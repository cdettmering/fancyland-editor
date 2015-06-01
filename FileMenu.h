#ifndef FILEMENU_H
#define FILEMENU_H

#include "Workspace.h"

#include <QObject>

class FileMenu : public QObject
{
    Q_OBJECT
public:
    FileMenu(Workspace *ws, QObject *parent = 0);

public slots:
    void save();
    void load();
    void settings();

private:
    Workspace *_ws;
};

#endif // FILEMENU_H
