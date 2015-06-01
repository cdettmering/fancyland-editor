#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ColorPushButton.h"

#include <QDialog>
#include <QPushButton>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = 0);

private slots:
    void handleTerrainLineColorChoose();
    void handleTerrainAnchorColorChoose();
    void handleItemBorderColorChoose();
    void handleAccepted();
    void handleRejected();

private:
    void setupUi();
    QColor chooseColor(const QColor &current);

    ColorPushButton *_terrainLineColorButton;
    ColorPushButton *_terrainAnchorColorButton;
    ColorPushButton *_itemBorderColorButton;

    QColor _newTerrainLineColor;
    QColor _newTerrainAnchorColor;
    QColor _newItemBorderColor;
};

#endif // SETTINGSDIALOG_H
