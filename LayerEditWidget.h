#ifndef LAYEREDITWIDGET_H
#define LAYEREDITWIDGET_H

#include "LayerEditScene.h"
#include "Palette.h"
#include "datatype/Level.h"

#include <QWidget>

class LayerEditWidget : public QWidget
{
    Q_OBJECT
public:
    LayerEditWidget(Level *level = 0, QWidget *parent = 0);

    Level * getLevel() const;
    void setLevel(Level *level);

signals:
    void dataChanged();

public slots:
    void handleDataChanged();
    void handleSpritesChanged(const QList<Sprite> &sprites);

private:
    void setupUi();
    Level *_level;
    Layer _bg;
    Layer _bfg;
    Layer _func;
    Layer _fg;
    LayerEditScene *_bgScene;
    LayerEditScene *_bfgScene;
    LayerEditScene *_funcScene;
    LayerEditScene *_fgScene;
    Palette *_palette;

    static const QString DISPLAY_NAME;
};

#endif // LAYEREDITWIDGET_H
