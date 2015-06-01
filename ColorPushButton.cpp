#include "ColorPushButton.h"

#include <QPainter>

ColorPushButton::ColorPushButton(QWidget *parent)
    : QPushButton(parent),
      _color(Qt::transparent)
{
}

void ColorPushButton::setColor(const QColor &color)
{
    _color = color;
    update();
}

QColor ColorPushButton::getColor() const
{
    return _color;
}

void ColorPushButton::paintEvent(QPaintEvent *event)
{
    //QPushButton::paintEvent(event);

    QPainter painter(this);
    painter.fillRect(rect(), _color);
}
