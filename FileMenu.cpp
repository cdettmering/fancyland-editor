#include "FileMenu.h"
#include "Dialog.h"
#include "SettingsDialog.h"

#include <QDebug>

FileMenu::FileMenu(Workspace *ws, QObject *parent)
    : QObject(parent),
      _ws(ws)
{

}

void FileMenu::save()
{
    qDebug() << "FileMenu::save - Saving level";
    _ws->saveLevel();
}

void FileMenu::load()
{
    qDebug() << "FileMenu::save - Loading level";
    _ws->loadLevel(Dialog::selectDirectory());
}

void FileMenu::settings()
{
    SettingsDialog *dialog = new SettingsDialog();
    dialog->exec();
}
