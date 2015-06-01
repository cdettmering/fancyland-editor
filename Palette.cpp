#include "Palette.h"
#include "BorderGraphicsPixmapItem.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

bool compareBySize(const Sprite &a, const Sprite &b)
{
    // Find the diagnol squared using pythagorean
    QSize aSize = a.getTexture().size();
    QSize bSize = b.getTexture().size();

    int aDiagnolSquared = aSize.width() * aSize.width() + aSize.height() * aSize.height();
    int bDiagnolSquared = bSize.width() * bSize.width() + bSize.height() * bSize.height();

    return aDiagnolSquared > bDiagnolSquared;
}

Palette::Palette(QObject *parent)
    : QGraphicsScene(parent),
      _previewSize(256, 256),
      _numberOfColumns(4),
      _gridVisible(false)

{

}

Palette::~Palette()
{

}

int Palette::getNumberOfColumns() const
{
    return _numberOfColumns;
}

void Palette::setNumberOfColumns(int columns)
{
    _numberOfColumns = columns;
    recalculatePositions();
}

QSize Palette::getPreviewSize() const
{
    return _previewSize;
}

void Palette::setPreviewSize(const QSize &size)
{
    resizeImages(_previewSize, size);
    _previewSize = size;
    recalculatePositions();
}

bool Palette::isGridVisible() const
{
    return _gridVisible;
}

void Palette::setGridVisible(bool visible)
{
    _gridVisible = visible;
}

QList<Sprite> Palette::getSprites() const
{
    return _sprites;
}

void Palette::setSprites(const QList<Sprite> &sprites)
{
    _sprites = sprites;

    qSort(_sprites.begin(), _sprites.end(), compareBySize);
    resizeImages(QSize(), _previewSize);

    recalculatePositions();
}

void Palette::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    // Palette does not accept any drops.
    event->ignore();
}

void Palette::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    // Palette does not accept any drops.
    event->ignore();
}

void Palette::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    // Palette does not accept any drops.
    event->ignore();
}

void Palette::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        _dragStartPosition = event->scenePos();
    }
    QGraphicsScene::mousePressEvent(event);
}

void Palette::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!event->buttons() & Qt::LeftButton) {
        return;
    }

    if((event->scenePos() - _dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }

    // Get the pixmap item related to the start of the drag.
    QGraphicsItem *item = itemAt(_dragStartPosition, QTransform());
    if(item == 0) {
        // Couldn't find an item at the location for some reason.
        return;
    }

    // Static cast is safe because this scene only adds QGraphicsPixmapItem
    QGraphicsPixmapItem *pixmapItem = static_cast<QGraphicsPixmapItem *>(item);
    Sprite sprite = _pixmapToSprite[pixmapItem];

    // Create a new drag event and put the source image into the mime data.
    QDrag *drag = new QDrag((QObject *)event->widget());
    QMimeData *data = new QMimeData();
    data->setImageData(sprite.getTexture());
    data->setText(sprite.getFileInfo().absoluteFilePath());
    drag->setMimeData(data);

    // Put the pixmap that was selected onto the cursor
    QPixmap pixmap = pixmapItem->pixmap();
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));

    // Execute the drag with a copy action.
    drag->exec(Qt::CopyAction, Qt::CopyAction);
}

void Palette::recalculatePositions()
{
    int row = 0;
    int column = 0;
    for(int i = 0; i < _previews.size(); i++) {
        if(column > _numberOfColumns) {
            column = 0;
            row++;
        }
        _previews.at(i)->setPos(QPointF(column * _previewSize.width(), row * _previewSize.height()));
        column++;
    }
}

void Palette::resizeImages(const QSize &oldSize, const QSize &newSize)
{
    if(oldSize != newSize) {
        for(int i = 0; i < _previews.size(); i++) {
            removeItem(_previews.at(i));
            delete _previews[i];
        }
        _previews.clear();
        _pixmapToSprite.clear();

        for(int i = 0; i < _sprites.size(); i++) {
            QImage sizedImage = _sprites.at(i).getTexture().scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem *pixmap = new BorderGraphicsPixmapItem(QPixmap::fromImage(sizedImage));
            addItem(pixmap);
            pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
            _pixmapToSprite.insert(pixmap, _sprites.at(i));
            _previews.append(pixmap);
        }
    }
}
