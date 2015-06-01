#include "LayerEditWidget.h"
#include "LayerSpeedControlWidget.h"

#include <qmath.h>
#include <QtAlgorithms>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QDebug>

const QString LayerEditWidget::DISPLAY_NAME = "Layer Edit";

LayerEditWidget::LayerEditWidget(Level *level, QWidget *parent)
    : QWidget(parent),
      _level(level),
      _bgScene(0),
      _bfgScene(0),
      _funcScene(0),
      _fgScene(0),
      _palette(0)
{
    if(_level != 0) {
        setLevel(_level);
    }
    setupUi();
}

Level * LayerEditWidget::getLevel() const
{
    return _level;
}

void LayerEditWidget::setLevel(Level *level)
{
    _level = level;
    if(_level != 0) {
        _bg = _level->getBackgroundLayer();
        _bfg = _level->getBackForegroundLayer();
        _func = _level->getFunctionalLayer();
        _fg = _level->getForegroundLayer();
    }
    // set level onto layer scenes
}

void LayerEditWidget::handleDataChanged()
{
    qDebug() << "LayerEditWidget::handleDataChanged - One or more layers have changed..syncing.";
    _level->setBackgroundLayer(_bg);
    _level->setBackForegroundLayer(_bfg);
    _level->setFunctionalLayer(_func);
    _level->setForegroundLayer(_fg);
    emit dataChanged();
}

void LayerEditWidget::handleSpritesChanged(const QList<Sprite> &sprites)
{
    qDebug() << "LayerEditWidget::handleSpritesChanged - Sprites have changed on disk...reogranizing.";
    if(_palette != 0) {
        _palette->setSprites(sprites);
    }
}

void LayerEditWidget::setupUi()
{
    // Initialize the LayerEditScene's
    if(_level != 0) {
        _bgScene = new LayerEditScene(&_bg);
        _bfgScene = new LayerEditScene(&_bfg);
        _funcScene = new LayerEditScene(&_func);
        _fgScene = new LayerEditScene(&_fg);
    } else {
        _bgScene = new LayerEditScene();
        _bfgScene = new LayerEditScene();
        _funcScene = new LayerEditScene();
        _fgScene = new LayerEditScene();
    }

    // Connect data changed signal to the widget's data changed signal
    connect(_bgScene, SIGNAL(dataChanged()), this, SLOT(handleDataChanged()));
    connect(_bfgScene, SIGNAL(dataChanged()), this, SLOT(handleDataChanged()));
    connect(_funcScene, SIGNAL(dataChanged()), this, SLOT(handleDataChanged()));
    connect(_fgScene, SIGNAL(dataChanged()), this, SLOT(handleDataChanged()));

    // Setup speed controllers
    LayerSpeedControlWidget *bgControl = new LayerSpeedControlWidget(tr("Background"));
    bgControl->setSpeed(_bg.getSpeed());
    connect(bgControl, SIGNAL(speedChanged(float)), _bgScene, SLOT(handleSpeedChange(float)));

    LayerSpeedControlWidget *bfgControl = new LayerSpeedControlWidget(tr("Back Foreground"));
    bfgControl->setSpeed(_bfg.getSpeed());
    connect(bfgControl, SIGNAL(speedChanged(float)), _bfgScene, SLOT(handleSpeedChange(float)));

    LayerSpeedControlWidget *funcControl = new LayerSpeedControlWidget(tr("Functional"));
    funcControl->setSpeed(_func.getSpeed());
    connect(funcControl, SIGNAL(speedChanged(float)), _funcScene, SLOT(handleSpeedChange(float)));

    LayerSpeedControlWidget *fgControl = new LayerSpeedControlWidget(tr("Foreground"));
    fgControl->setSpeed(_fg.getSpeed());
    connect(fgControl, SIGNAL(speedChanged(float)), _fgScene, SLOT(handleSpeedChange(float)));

    // Initialize the viewers for each
    QGraphicsView *bgView = new QGraphicsView(_bgScene);
    bgView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QGraphicsView *bfgView = new QGraphicsView(_bfgScene);
    bfgView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QGraphicsView *funcView = new QGraphicsView(_funcScene);
    funcView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QGraphicsView *fgView = new QGraphicsView(_fgScene);
    fgView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Initialize the palette
    _palette = new Palette();
    _palette->setPreviewSize(QSize(228, 128));

    // Grab all unique sprites from all layers
    /*QList<Sprite> allSprites;
    for(int i = 0; i < _bg.getSprites().size(); i++) {
        if(!allSprites.contains(_bg.getSprites().at(i))) {
            allSprites.append(_bg.getSprites().at(i));
        }
    }
    for(int i = 0; i < _bfg.getSprites().size(); i++) {
        if(!allSprites.contains(_bfg.getSprites().at(i))) {
            allSprites.append(_bfg.getSprites().at(i));
        }
    }
    for(int i = 0; i < _func.getSprites().size(); i++) {
        if(!allSprites.contains(_func.getSprites().at(i))) {
            allSprites.append(_func.getSprites().at(i));
        }
    }
    for(int i = 0; i < _fg.getSprites().size(); i++) {
        if(!allSprites.contains(_fg.getSprites().at(i))) {
            allSprites.append(_fg.getSprites().at(i));
        }
    }*/

    //_palette->setSprites(allSprites);

    // Initliaze palette viewer
    QGraphicsView *paletteView = new QGraphicsView(_palette);
    paletteView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Separate into groups
    QGroupBox *paletteGroup = new QGroupBox(tr("Palette"));
    QVBoxLayout *paletteLayout = new QVBoxLayout();
    paletteLayout->addWidget(paletteView);

    QGroupBox *layerGroup = new QGroupBox(tr("Layers"));
    QVBoxLayout *layerLayout = new QVBoxLayout();

    // Group together the speed controls with the edit views.
    QHBoxLayout *bgLayout = new QHBoxLayout();
    bgLayout->addWidget(bgControl);
    bgLayout->addWidget(bgView);

    QHBoxLayout *bfgLayout = new QHBoxLayout();
    bfgLayout->addWidget(bfgControl);
    bfgLayout->addWidget(bfgView);

    QHBoxLayout *funcLayout = new QHBoxLayout();
    funcLayout->addWidget(funcControl);
    funcLayout->addWidget(funcView);

    QHBoxLayout *fgLayout = new QHBoxLayout();
    fgLayout->addWidget(fgControl);
    fgLayout->addWidget(fgView);

    layerLayout->addLayout(bgLayout);
    layerLayout->addLayout(bfgLayout);
    layerLayout->addLayout(funcLayout);
    layerLayout->addLayout(fgLayout);

    // Set group layouts
    paletteGroup->setLayout(paletteLayout);
    layerGroup->setLayout(layerLayout);

    // Set main layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(paletteGroup);
    layout->addWidget(layerGroup);

    setLayout(layout);
    setWindowTitle(DISPLAY_NAME);
}
