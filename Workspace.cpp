#include "Workspace.h"

#include "readerwriter/LevelFileReaderWriter.h"
#include "readerwriter/EnemyMapFileReaderWriter.h"
#include "readerwriter/LayerFileReaderWriter.h"
#include "readerwriter/TerrainFileReaderWriter.h"
#include "readerwriter/EnemyFileReaderWriter.h"

#include "datatype/Terrain.h"
#include "datatype/Layer.h"
#include "datatype/EnemyMap.h"
#include "datatype/Enemy.h"

#include <QDebug>

Workspace::Workspace(QObject *parent)
    : QObject(parent),
      _levelOpen(false)
{

}

QDir Workspace::getRootDirectory() const
{
    return _rootDirectory;
}

QDir Workspace::getEnemyDirectory() const
{
    QDir enemyDirectory = getRootDirectory();
    enemyDirectory.cd("enemies");
    return enemyDirectory;
}

QDir Workspace::getTextureDirectory() const
{
    QDir textureDirectory = getRootDirectory();
    textureDirectory.cd("textures");
    return textureDirectory;
}

QList<Sprite> Workspace::getSprites() const
{
    QDir textureDir = getTextureDirectory();

    // Get all images. Assume this directory only contains images.
    QFileInfoList images = textureDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    QList<Sprite> sprites;
    for(int i = 0; i < images.size(); i++) {
        Sprite sprite(QImage(images.at(i).absoluteFilePath()), images.at(i).absoluteFilePath());
        sprites.append(sprite);
    }
    return sprites;
}

void Workspace::newLevel(const QString &path)
{
    QDir directory(path);
    if(directory.exists()) {
        //create level
    }
}

void Workspace::loadLevel(const QString &path)
{
    QDir directory(path);
    if(directory.exists()) {
        qDebug() << "Workspace::loadLevel - Loading level " << path;
        _rootDirectory = directory;

        // Read the level file
        LevelFileReaderWriter levelReaderWriter;
        levelReaderWriter.read(getRootDirectory().absolutePath() + QString("/main.level"), _levelFile);

        // Read the enemy map file
        EnemyMapFile enemyMapFile;
        EnemyMapFileReaderWriter enemyMapReaderWriter;
        enemyMapReaderWriter.read(getRootDirectory().absolutePath() + QString("/") + _levelFile.getEnemyMapFile(), enemyMapFile);

        // Read the terrain file
        TerrainFile terrainFile;
        TerrainFileReaderWriter terrainReaderWriter;
        terrainReaderWriter.read(getRootDirectory().absolutePath() + QString("/") + _levelFile.getTerrainFile(), terrainFile);

        // Read background layer file
        LayerFile bgLayerFile;
        LayerFileReaderWriter layerReaderWriter;
        layerReaderWriter.read(getRootDirectory().absolutePath() + QString("/") + _levelFile.getBackgroundLayerFile(), bgLayerFile);

        // Read backforeground layer file
        LayerFile bfgLayerFile;
        layerReaderWriter.read(getRootDirectory().absolutePath() + QString("/") + _levelFile.getBackForegroundLayerFile(), bfgLayerFile);

        // Read functional layer file
        LayerFile funcLayerFile;
        layerReaderWriter.read(getRootDirectory().absolutePath() + QString("/") + _levelFile.getFunctionalLayerFile(), funcLayerFile);

        // Read foreground layer file
        LayerFile fgLayerFile;
        layerReaderWriter.read(getRootDirectory().absolutePath() + QString("/") + _levelFile.getForegroundLayerFile(), fgLayerFile);

        // Populate enemy map
        QList<QPair<QPointF, Enemy> > enemies;
        QMap<QString, QString> dictionary = enemyMapFile.getDictionary();
        EnemyFileReaderWriter enemyFileReaderWriter;

        // Load each enemy
        for(int i = 0; i < enemyMapFile.getEnemies().size(); i++) {
            QPair<QPointF, QString> posEnemyPair = enemyMapFile.getEnemies().at(i);
            QString eStr = getEnemyDirectory().absolutePath() + QString("/");
            eStr += dictionary[posEnemyPair.second];
            EnemyFile enemyFile;
            enemyFileReaderWriter.read(eStr, enemyFile);
            QString sStr = getTextureDirectory().absolutePath() + QString("/");
            sStr += enemyFile.getSpriteFile();
            Enemy enemy(enemyFile.getType(), posEnemyPair.first, sStr, enemyFile.getBody());
            enemies.append(QPair<QPointF, Enemy>(posEnemyPair.first, enemy));
        }

        EnemyMap enemyMap(enemyMapFile.getDictionary(), enemies);

        // Populate terrain
        Terrain terrain(terrainFile.getPolygons().toVector());

        // Populate background layer
        QStringList bgSpriteFiles = bgLayerFile.getTextures();
        QList<Sprite> bgSprites;
        for(int i = 0; i < bgSpriteFiles.size(); i++) {
            QString filepath = getTextureDirectory().absolutePath() + QString("/") + bgSpriteFiles.at(i);
            Sprite sprite(QImage(filepath), filepath);
            bgSprites.append(sprite);
        }
        Layer bgLayer(bgLayerFile.getSpeed(), bgSprites);

        // Populate backforeground layer
        QStringList bfgSpriteFiles = bfgLayerFile.getTextures();
        QList<Sprite> bfgSprites;
        for(int i = 0; i < bfgSpriteFiles.size(); i++) {
            QString filepath = getTextureDirectory().absolutePath() + QString("/") + bfgSpriteFiles.at(i);
            Sprite sprite(QImage(filepath), filepath);
            bfgSprites.append(sprite);
        }
        Layer bfgLayer(bfgLayerFile.getSpeed(), bfgSprites);

        // Populate functional layer
        QStringList funcSpriteFiles = funcLayerFile.getTextures();
        QList<Sprite> funcSprites;
        for(int i = 0; i < funcSpriteFiles.size(); i++) {
            QString filepath = getTextureDirectory().absolutePath() + QString("/") + funcSpriteFiles.at(i);
            Sprite sprite(QImage(filepath), filepath);
            funcSprites.append(sprite);
        }
        Layer funcLayer(funcLayerFile.getSpeed(), funcSprites);

        // Populate foreground layer
        QStringList fgSpriteFiles = fgLayerFile.getTextures();
        QList<Sprite> fgSprites;
        for(int i = 0; i < fgSpriteFiles.size(); i++) {
            QString filepath = getTextureDirectory().absolutePath() + QString("/") + fgSpriteFiles.at(i);
            Sprite sprite(QImage(filepath), filepath);
            fgSprites.append(sprite);
        }
        Layer fgLayer(fgLayerFile.getSpeed(), fgSprites);

        // Populate level
        _level.setStartPoint(_levelFile.getStartPoint());
        _level.setFinishLine(_levelFile.getFinishLine());
        _level.setTimeToComplete(_levelFile.getTimeToComplete());
        _level.setEnemyMap(enemyMap);
        _level.setTerrain(terrain);
        _level.setBackgroundLayer(bgLayer);
        _level.setBackForegroundLayer(bfgLayer);
        _level.setFunctionalLayer(funcLayer);
        _level.setForegroundLayer(fgLayer);

        _levelOpen = true;
        emit levelLoaded(&_level);
    } else {
        //failed
        qDebug() << "Workspace::loadLevel - Failed to load level " << path << " directory does not exist.";
        _levelOpen = false;
    }
}

void Workspace::saveLevel()
{
    qDebug() << "Workspace::saveLevel - Saving " << _levelOpen;
    if(_levelOpen) {
        // Sync with all editing tools
        for(int i = 0; i < _tools.size(); i++) {
            _tools.at(i)->sync(&_level);
        }
        // Create the level file from the ground up

        // Create background layer file
        LayerFile bgLayerFile;
        bgLayerFile.setSpeed(_level.getBackgroundLayer().getSpeed());
        bgLayerFile.setTexturesFromSpriteList(_level.getBackgroundLayer().getSprites());

        // Create backForeground layer file
        LayerFile bfgLayerFile;
        bfgLayerFile.setSpeed(_level.getBackForegroundLayer().getSpeed());
        bfgLayerFile.setTexturesFromSpriteList(_level.getBackForegroundLayer().getSprites());

        // Create functional layer file
        LayerFile funcLayerFile;
        funcLayerFile.setSpeed(_level.getFunctionalLayer().getSpeed());
        funcLayerFile.setTexturesFromSpriteList(_level.getFunctionalLayer().getSprites());

        // Create foreground layer file
        LayerFile fgLayerFile;
        fgLayerFile.setSpeed(_level.getForegroundLayer().getSpeed());
        fgLayerFile.setTexturesFromSpriteList(_level.getForegroundLayer().getSprites());

        // Create terrain file
        TerrainFile terrainFile;
        terrainFile.setPolygons(_level.getTerrain().toList());

        // Create enemy map file
        EnemyMapFile enemyMapFile;
        enemyMapFile.setDictionary(_level.getEnemyMap().getDictionary());
        enemyMapFile.setEnemiesFromEnemyList(_level.getEnemyMap().getEnemies());

        // Create the level file
        _levelFile.setStartPoint(_level.getStartPoint());
        _levelFile.setFinishLine(_level.getFinishLine());
        _levelFile.setTimeToComplete(_level.getTimeToComplete());

        // Write out data
        LayerFileReaderWriter layerReaderWriter;
        layerReaderWriter.write(getRootDirectory().absolutePath() + QString("/") + _levelFile.getBackgroundLayerFile(), bgLayerFile);
        layerReaderWriter.write(getRootDirectory().absolutePath() + QString("/") + _levelFile.getBackForegroundLayerFile(), bfgLayerFile);
        layerReaderWriter.write(getRootDirectory().absolutePath() + QString("/") + _levelFile.getFunctionalLayerFile(), funcLayerFile);
        layerReaderWriter.write(getRootDirectory().absolutePath() + QString("/") + _levelFile.getForegroundLayerFile(), fgLayerFile);

        TerrainFileReaderWriter terrainReaderWriter;
        terrainReaderWriter.write(getRootDirectory().absolutePath() + QString("/") + _levelFile.getTerrainFile(), terrainFile);

        EnemyMapFileReaderWriter enemyMapReaderWriter;
        enemyMapReaderWriter.write(getRootDirectory().absolutePath() + QString("/") + _levelFile.getEnemyMapFile(), enemyMapFile);

        LevelFileReaderWriter levelReaderWriter;
        levelReaderWriter.write(getRootDirectory().absolutePath() + QString("/main.level"), _levelFile);
    }
}

void Workspace::registerEditTool(EditTool *tool)
{
    _tools.append(tool);
}

void Workspace::unregisterEditTool(EditTool *tool)
{
    _tools.remove(_tools.indexOf(tool));
}
