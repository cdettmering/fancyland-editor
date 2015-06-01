#include "SettingsDialog.h"
#include "Settings.h"

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent),
      _newTerrainLineColor(Settings::getTerrainLineColor()),
      _newItemBorderColor(Settings::getItemBorderColor())
{
    setupUi();
}

void SettingsDialog::handleTerrainLineColorChoose()
{
    _newTerrainLineColor = chooseColor(Settings::getTerrainLineColor());
    _terrainLineColorButton->setColor(_newTerrainLineColor);
    qDebug() << "SettingsDialog::handleTerrainColorChoose - Setting terrain line color to " << _newTerrainLineColor;
}

void SettingsDialog::handleTerrainAnchorColorChoose()
{
    _newTerrainAnchorColor = chooseColor(Settings::getTerrainAnchorColor());
    _terrainAnchorColorButton->setColor(_newTerrainAnchorColor);
    qDebug() << "SettingsDialog::handleTerrainAnchorColorChoose - Setting terrain Anchor color to " << _newTerrainAnchorColor;
}

void SettingsDialog::handleItemBorderColorChoose()
{
    _newItemBorderColor = chooseColor(Settings::getItemBorderColor());
    _itemBorderColorButton->setColor(_newItemBorderColor);
    qDebug() << "SettingsDialog::handleItemBorderColorChoose - Setting item border color to " << _newItemBorderColor;
}

void SettingsDialog::setupUi()
{
    setWindowTitle(tr("Settings"));

    QLabel *terrainLineColorLabel = new QLabel(tr("Terrain Line Color"));
    QLabel *terrainAnchorColorLabel = new QLabel(tr("Terrain Anchor Color"));
    QLabel *itemBorderColorLabel = new QLabel(tr("Item Border Color"));

    _terrainLineColorButton = new ColorPushButton();
    _terrainLineColorButton->setColor(Settings::getTerrainLineColor());
    connect(_terrainLineColorButton, SIGNAL(clicked()), this, SLOT(handleTerrainLineColorChoose()));

    _terrainAnchorColorButton = new ColorPushButton();
    _terrainAnchorColorButton->setColor(Settings::getTerrainAnchorColor());
    connect(_terrainAnchorColorButton, SIGNAL(clicked()), this, SLOT(handleTerrainAnchorColorChoose()));

    _itemBorderColorButton = new ColorPushButton();
    _itemBorderColorButton->setColor(Settings::getItemBorderColor());
    connect(_itemBorderColorButton, SIGNAL(clicked()), this, SLOT(handleItemBorderColorChoose()));

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(terrainLineColorLabel, _terrainLineColorButton);
    formLayout->addRow(terrainAnchorColorLabel, _terrainAnchorColorButton);
    formLayout->addRow(itemBorderColorLabel, _itemBorderColorButton);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(formLayout);
    layout->addWidget(buttonBox);

    setLayout(layout);

    connect(this, SIGNAL(accepted()), this, SLOT(handleAccepted()));
    connect(this, SIGNAL(rejected()), this, SLOT(handleRejected()));
}

QColor SettingsDialog::chooseColor(const QColor &current)
{
    qDebug() << "SettingsDialog::chooseColor - Opening color chooser";
    QColor color = QColorDialog::getColor();
    if(!color.isValid()) {
        qDebug() << "SettingsDialog::chooseColor - Color invalid reverting to " << current;
        color = current;
    }
    return color;
}

void SettingsDialog::handleAccepted()
{
    qDebug() << "SettingsDialog::handleAccepted - Committing changes";
    Settings::setTerrainLineColor(_newTerrainLineColor);
    Settings::setTerrainAnchorColor(_newTerrainAnchorColor);
    Settings::setItemBorderColor(_newItemBorderColor);
}

void SettingsDialog::handleRejected()
{
    qDebug() << "SettingsDialog::handleRejected - Reverting changes";
}
