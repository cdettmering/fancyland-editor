#ifndef COLORPUSHBUTTON_H
#define COLORPUSHBUTTON_H

#include <QPushButton>

class ColorPushButton : public QPushButton
{
    Q_OBJECT

public:
    ColorPushButton(QWidget *parent = 0);

    void setColor(const QColor &color);
    QColor getColor() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor _color;
};

#endif // COLORPUSHBUTTON_H
