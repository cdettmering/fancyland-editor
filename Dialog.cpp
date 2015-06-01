#include "Dialog.h"

#include <QFileDialog>

QList<Sprite> Dialog::selectSprites()
{
    QStringList files = QFileDialog::getOpenFileNames
            (0, QObject::tr("Open Sprites"), ".", QObject::tr("Image Files ) *.bmp *.jpg *.jpeg *.png *.pbm *.ppm *.tiff *.xbm *.xpm"));
    QList<Sprite> sprites;
    for(int i = 0; i < files.size(); i++) {
        QImage image(files.at(i));
        if(!image.isNull()) {
            Sprite sprite(image, files.at(i));
            sprites.append(sprite);
        }
    }
    return sprites;
}

QString Dialog::selectDirectory()
{
    return QFileDialog::getExistingDirectory(0, QObject::tr("Select a Directory"));
}
