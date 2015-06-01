#include "LayerSpeedControlWidget.h"

#include <QLabel>
#include <QVBoxLayout>

LayerSpeedControlWidget::LayerSpeedControlWidget(const QString &layerName, QWidget *parent)
    : QWidget(parent)
{
    setupUi(layerName);
}

void LayerSpeedControlWidget::setSpeed(float speed)
{
    _speedControl->setValue(speed);
}

float LayerSpeedControlWidget::getSpeed() const
{
    return _speedControl->value();
}

void LayerSpeedControlWidget::setupUi(const QString &layerName)
{
    QVBoxLayout *layout = new QVBoxLayout();

    //create the name of the layer in bold
    QLabel *boldName = new QLabel();
    QString bold = "<b>";
    bold.append(layerName);
    bold.append("</b>");
    boldName->setText(bold);

    QLabel *speedLabel = new QLabel(tr("Speed"));
    _speedControl = new QDoubleSpinBox();
    _speedControl->setDecimals(3);
    _speedControl->setValue(1.0);
    _speedControl->setMinimum(0);
    _speedControl->setSingleStep(0.1);
    _speedControl->setFocusPolicy(Qt::ClickFocus);

    connect(_speedControl, SIGNAL(valueChanged(double)), this, SLOT(handleSpeedChange(double)));

    QHBoxLayout *speedLayout = new QHBoxLayout();
    speedLayout->addWidget(speedLabel);
    speedLayout->addWidget(_speedControl);

    layout->addWidget(boldName);
    layout->addLayout(speedLayout);

    setLayout(layout);
}

void LayerSpeedControlWidget::handleSpeedChange(double speed)
{
    emit speedChanged((float)speed);
}
