#include "ImportMenu.h"
#include "Dialog.h"

#include <QImageWriter>
#include <QDebug>

ImportMenu::ImportMenu(Workspace *ws, QObject *parent)
    : QObject(parent),
      _ws(ws)
{

}

void ImportMenu::importSprites()
{
    qDebug() << "ImportMenu::importSprites - Opening sprite selection dialog.";
    // Open menu for the user to select sprites.
    QList<Sprite> sprites = Dialog::selectSprites();

    // Use the Workspace object to write the sprites into the texture
    // directory.
    QDir textureDirectory = _ws->getTextureDirectory();
    qDebug() << "ImportMenu::importSprites - Importing sprites into " << textureDirectory;
    for(int i = 0; i < sprites.size(); i++) {
        QString filename = sprites.at(i).getFileInfo().fileName();
        QString filepath = textureDirectory.absolutePath() + QString("/") + filename;

        // Remove the native extension from filepath
        filepath = filepath.remove(filepath.indexOf('.'), filepath.length());

        // Add on png
        filepath += QString(".png");
        qDebug() << "ImportMenu::importSprites - Writing " << filepath;
        QImageWriter writer(filepath);
        writer.write(sprites.at(i).getTexture());
    }

    emit spritesChanged(_ws->getSprites());
}

void ImportMenu::importEnemies()
{

}
