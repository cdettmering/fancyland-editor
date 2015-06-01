#ifndef LAYERSPEEDCONTROLWIDGET_H
#define LAYERSPEEDCONTROLWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>

class LayerSpeedControlWidget : public QWidget
{
    Q_OBJECT
public:
    LayerSpeedControlWidget(const QString &layerName, QWidget *parent = 0);

    void setSpeed(float speed);
    float getSpeed() const;

signals:
    void speedChanged(float speed);

private slots:
    void handleSpeedChange(double speed);

private:
    void setupUi(const QString &layerName);
    QDoubleSpinBox *_speedControl;
};

#endif // LAYERSPEEDCONTROLWIDGET_H
