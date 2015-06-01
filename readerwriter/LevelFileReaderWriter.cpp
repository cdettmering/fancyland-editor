#include "LevelFileReaderWriter.h"
#include "LuaUtil.h"

#include <QFile>
#include <QDir>
#include <QDebug>

#include <luabind/object.hpp>
#include <luabind/function.hpp>
#include <luabind/error.hpp>


LevelFileReaderWriter::LevelFileReaderWriter()
    : ReaderWriter<LevelFile>()
{

}

LevelFileReaderWriter::~LevelFileReaderWriter()
{

}

bool LevelFileReaderWriter::read(const QString &file, LevelFile &object) const
{
    lua_State *state = 0;
    try {
        qDebug() << "LevelFileReaderWriter::read - Reading " << file;
        luabind::object levelTable;
        state = LuaUtil::openFile(file, &levelTable);
        if(state == 0) {
            return false;
        }

        // Get file properties
        qDebug() << "LevelFileReaderWriter::read - Reading file properties";

        // Get start point
        luabind::object startPointTable = levelTable["startPoint"];
        float x = luabind::object_cast<float>(startPointTable["x"]);
        float y = luabind::object_cast<float>(startPointTable["y"]);
        QPointF startPoint(x, y);
        qDebug() << "LevelFileReaderWriter::read - StartPoint " << startPoint;

        // Get finish line
        int finishLine = luabind::object_cast<int>(levelTable["finishLine"]);
        qDebug() << "LevelFileReaderWriter::read - FinishLine " << finishLine;

        // Get time to complete
        int timeToComplete = luabind::object_cast<int>(levelTable["timeToComplete"]);
        qDebug() << "LevelFileReaderWriter::read - TimeToComplete " << timeToComplete;

        // Get enemy file
        std::string enemyFileString = luabind::object_cast<std::string>(levelTable["enemyFile"]);
        QString enemyFile(enemyFileString.c_str());
        qDebug() << "LevelFileReaderWriter::read - EnemyFile " << enemyFile;

        // Get terrain file
        std::string terrainFileString = luabind::object_cast<std::string>(levelTable["terrainFile"]);
        QString terrainFile(terrainFileString.c_str());
        qDebug() << "LevelFileReaderWriter::read - TerrainFile " << terrainFile;

        // Get backgroundLayer file
        std::string backgroundLayerFileString = luabind::object_cast<std::string>(levelTable["backgroundLayerFile"]);
        QString backgroundLayerFile(backgroundLayerFileString.c_str());
        qDebug() << "LevelFileReaderWriter::read - BackgroundLayerFile " << backgroundLayerFile;

        // Get backForegroundLayer file
        std::string backForegroundLayerFileString = luabind::object_cast<std::string>(levelTable["backForegroundLayerFile"]);
        QString backForegroundLayerFile(backForegroundLayerFileString.c_str());
        qDebug() << "LevelFileReaderWriter::read - BackForegroundLayerFile " << backForegroundLayerFile;

        // Get functionalLayer file
        std::string functionalLayerFileString = luabind::object_cast<std::string>(levelTable["functionalLayerFile"]);
        QString functionalLayerFile(functionalLayerFileString.c_str());
        qDebug() << "LevelFileReaderWriter::read - FunctionalLayerFile " << functionalLayerFile;

        // Get foregroundLayer file
        std::string foregroundLayerFileString = luabind::object_cast<std::string>(levelTable["foregroundLayerFile"]);
        QString foregroundLayerFile(foregroundLayerFileString.c_str());
        qDebug() << "LevelFileReaderWriter::read - ForegroundLayerFile " << foregroundLayerFile;

        // Set data onto object
        qDebug() << "LevelFileReaderWriter::read - Setting data into memory object";
        object.setStartPoint(startPoint);
        object.setFinishLine(finishLine);
        object.setTimeToComplete(timeToComplete);
        object.setEnemyMapFile(enemyFile);
        object.setTerrainFile(terrainFile);
        object.setBackgroundLayerFile(backgroundLayerFile);
        object.setBackForegroundLayerFile(backForegroundLayerFile);
        object.setFunctionalLayerFile(functionalLayerFile);
        object.setForegroundLayerFile(foregroundLayerFile);

    } catch(luabind::error &lbError) {
        qDebug() << "LevelFileReaderWriter::read - Luabind Error " << LuaUtil::getErrorMessage(lbError.state());
        lua_close(lbError.state());
        return false;
    }
    lua_close(state);
    return true;
}

bool LevelFileReaderWriter::write(const QString &file, const LevelFile &object) const
{
    qDebug() << "LevelFileReaderWriter::write - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "LevelFileReaderWriter::write - Failed to open, returning false.";
        return false;
    }
    qDebug() << "LevelFileReaderWriter::write - Successfully opened, writing data.";
    QTextStream stream(&diskFile);
    stream << "local Point = require(MATHPATH .. \'Point\')" << endl << endl;
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "    startPoint = Point:new(" << (int)object.getStartPoint().x() << ", " << (int)object.getStartPoint().y() << ")," << endl;
    stream << "    finishLine = " << object.getFinishLine() << "," << endl;
    stream << "    timeToComplete = " << object.getTimeToComplete() << "," << endl;
    stream << "    enemyFile = \'" << object.getEnemyMapFile() << "\'," << endl;
    stream << "    terrainFile = \'" << object.getTerrainFile() << "\'," << endl;
    stream << "    backgroundLayerFile = \'" << object.getBackgroundLayerFile() << "\'," << endl;
    stream << "    backForegroundLayerFile = \'" << object.getBackForegroundLayerFile() << "\'," << endl;
    stream << "    functionalLayerFile = \'" << object.getFunctionalLayerFile() << "\'," << endl;
    stream << "    foregroundLayerFile = \'" << object.getForegroundLayerFile() << "\'" << endl;
    stream << "}";
    qDebug() << "LevelFileReaderWriter::write - Returning true.";
    return true;
}

bool LevelFileReaderWriter::createDefaultFile(const QString &file) const
{
    qDebug() << "LevelFileReaderWriter::createDefaultFile - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "LevelFileReaderWriter::createDefaultFile - Failed to open, returning false.";
        return false;
    }
    qDebug() << "LevelFileReaderWriter::createDefaultFile - Successfully opened, writing data.";
    QTextStream stream(&diskFile);
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "    startPoint = Point:new(0,0)," << endl;
    stream << "    finishLine = 0," << endl;
    stream << "    timeToComplete = 0," << endl;
    stream << "    enemyFile = \'\'," << endl;
    stream << "    terrainFile = \'\'," << endl;
    stream << "    backgroundLayerFile = \'\'," << endl;
    stream << "    backForegroundLayerFile = \'\'," << endl;
    stream << "    functionalLayerFile = \'\'," << endl;
    stream << "    foregroundLayerFile = \'\'" << endl;
    stream << "}";
    qDebug() << "LevelFileReaderWriter::createDefaultFile - Returning true.";
    return true;
}

bool LevelFileReaderWriter::createDirectoryStructure(const QString &path, const QString &levelName) const
{
    QDir directory(path);
    if(directory.exists()) {
        if(directory.mkdir(levelName)) {
            directory.cd(levelName);
            if(directory.mkdir("textures") && directory.mkdir("enemies")) {
                directory.cd("enemies");
                if(directory.mkdir("implementation")) {
                    return true;
                }
            }
        }
    }
    return false;
}
