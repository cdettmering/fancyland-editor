#ifndef BORDERGRAPHICSPIXMAPITEM_H
#define BORDERGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>

class BorderGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    BorderGraphicsPixmapItem(QGraphicsItem *parent = 0);
    BorderGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = 0);

    virtual ~BorderGraphicsPixmapItem() {}

    void setBorderWidth(int width);
    int getBorderWidth() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int _width;
};

#endif // BORDERGRAPHICSPIXMAPITEM_H
