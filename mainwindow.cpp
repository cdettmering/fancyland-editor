#include "mainwindow.h"

#include <QToolBar>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _level(0),
    _scene(0),
    _tool(0),
    _view(0),
    _layerEditWidget(0)
{
    load();
    createToolbarAndMenubar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setTerrainTool()
{
    if(_scene != 0) {
        _scene->setTool(_tool);
        _toolbar->addActions(_tool->getActions());
    }
}

void MainWindow::setSelectionTool()
{
    if(_scene != 0) {
        _scene->setTool(0);
        for(int i = 0; i < _tool->getActions().size(); i++) {
            _toolbar->removeAction(_tool->getActions().at(i));
        }
    }
}

void MainWindow::handleLevelLoad(Level *level)
{
    _level = level;
    if(_scene != 0) {
        delete _scene;
    }
    _scene = new EditScene(_level);

    if(_tool != 0) {
        delete _tool;
    }
    _tool = new TerrainEditTool(_scene);
    _ws->registerEditTool(_tool);
    _view->setScene(_scene);

    if(_layerEditWidget != 0) {
        disconnect(_scene, SLOT(handleLayerChanged()));
        delete _layerEditWidget;
    }
    _layerEditWidget = new LayerEditWidget(_level);
    _layerEditWidget->handleSpritesChanged(_ws->getSprites());
    connect(_layerEditWidget, SIGNAL(dataChanged()), _scene, SLOT(handleLayerChanged()));
    connect(_importMenu, SIGNAL(spritesChanged(QList<Sprite>)), _layerEditWidget, SLOT(handleSpritesChanged(QList<Sprite>)));
    _layerEditWidget->show();
}

void MainWindow::load()
{
    _ws = new Workspace();
    connect(_ws, SIGNAL(levelLoaded(Level*)), this, SLOT(handleLevelLoad(Level*)));
    _importMenu = new ImportMenu(_ws);
    _fileMenu = new FileMenu(_ws);
    _view = new QGraphicsView();
    _view->setAlignment(Qt::AlignHCenter | Qt::AlignLeft);
    _view->setMinimumHeight(720);
    _view->setMinimumWidth(1280);
    _view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setCentralWidget(_view);
}

void MainWindow::createToolbarAndMenubar()
{
    // Create toolbar
    _toolbar = new QToolBar();

    QActionGroup *toolGroup = new QActionGroup(this);

    QAction *selectionToolAction = new QAction(toolGroup);
    selectionToolAction->setText(tr("Selection Tool"));
    selectionToolAction->setIcon(QIcon(":images/icons/selectiontool.png"));
    selectionToolAction->setCheckable(true);
    connect(selectionToolAction, SIGNAL(triggered()), this, SLOT(setSelectionTool()));

    QAction *terrainToolAction = new QAction(toolGroup);
    //terrainToolAction->setText(_tool->getDisplayName());
    terrainToolAction->setIcon(QIcon(":images/icons/terraintool.png"));
    terrainToolAction->setCheckable(true);
    connect(terrainToolAction, SIGNAL(triggered()), this, SLOT(setTerrainTool()));

    toolGroup->addAction(selectionToolAction);
    toolGroup->addAction(terrainToolAction);
    _toolbar->addActions(toolGroup->actions());

    addToolBar(Qt::LeftToolBarArea, _toolbar);

    // Create menu bar
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *loadAction = new QAction(fileMenu);
    loadAction->setText(tr("Load"));
    connect(loadAction, SIGNAL(triggered()), _fileMenu, SLOT(load()));
    fileMenu->addAction(loadAction);
    QAction *saveAction = new QAction(fileMenu);
    saveAction->setText(tr("Save"));
    connect(saveAction, SIGNAL(triggered()), _fileMenu, SLOT(save()));
    fileMenu->addAction(saveAction);
    QAction *settingsAction = new QAction(fileMenu);
    settingsAction->setText(tr("Settings"));
    connect(settingsAction, SIGNAL(triggered()), _fileMenu, SLOT(settings()));
    fileMenu->addAction(settingsAction);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    //QMenu *terrainToolMenu = toolsMenu->addMenu(tr("Terrain"));
    //terrainToolMenu->addActions(_tool->getActions());

    QMenu *importMenu = menuBar()->addMenu(tr("&Import"));
    QAction *importSpriteAction = new QAction(importMenu);
    importSpriteAction->setText(tr("Sprites"));
    connect(importSpriteAction, SIGNAL(triggered()), _importMenu, SLOT(importSprites()));
    importMenu->addAction(importSpriteAction);
}
