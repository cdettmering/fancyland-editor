#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "datatype/Level.h"
#include "EditScene.h"
#include "tools/TerrainEditTool.h"
#include "Workspace.h"
#include "ImportMenu.h"
#include "FileMenu.h"
#include "LayerEditWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setTerrainTool();
    void setSelectionTool();
    void handleLevelLoad(Level *level);
    
private:
    void load();
    void createToolbarAndMenubar();
    QToolBar *_toolbar;
    Level *_level;
    EditScene *_scene;
    TerrainEditTool *_tool;
    Workspace *_ws;
    ImportMenu *_importMenu;
    FileMenu *_fileMenu;
    QGraphicsView *_view;
    LayerEditWidget *_layerEditWidget;
};

#endif // MAINWINDOW_H
