#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "EditTool.h"
#include "datatype/Level.h"
#include "file/LevelFile.h"

#include <QDir>
#include <QObject>

class Workspace : public QObject
{
    Q_OBJECT
public:
    Workspace(QObject *parent = 0);

    QDir getRootDirectory() const;
    QDir getTextureDirectory() const;
    QDir getEnemyDirectory() const;

    QList<Sprite> getSprites() const;

    void newLevel(const QString &path);
    void loadLevel(const QString &path);
    void saveLevel();

    void registerEditTool(EditTool *tool);
    void unregisterEditTool(EditTool *tool);

signals:
    void levelLoaded(Level *level);

private:
    QDir _rootDirectory;
    Level _level;
    LevelFile _levelFile;
    bool _levelOpen;
    QVector<EditTool *> _tools;
};

#endif // WORKSPACE_H
