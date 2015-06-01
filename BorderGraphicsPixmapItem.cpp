#include "BorderGraphicsPixmapItem.h"
#include "Settings.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

BorderGraphicsPixmapItem::BorderGraphicsPixmapItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      _width(3)
{
}

BorderGraphicsPixmapItem::BorderGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent),
      _width(3)
{

}

void BorderGraphicsPixmapItem::setBorderWidth(int width)
{
    _width = width;
}

int BorderGraphicsPixmapItem::getBorderWidth() const
{
    return _width;
}

void BorderGraphicsPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Paint as normal, not selected
    QStyleOptionGraphicsItem fake;
    QGraphicsPixmapItem::paint(painter, &fake, widget);

    if(option->state & QStyle::State_Selected) {

        // Add the custom border
        painter->save();

        // Set color and width
        QPen pen = painter->pen();
        pen.setColor(Settings::getItemBorderColor());
        pen.setWidth(_width);
        painter->setPen(pen);

        // Draw a rect
        painter->drawRect(pixmap().rect());


        painter->restore();
    }
}
