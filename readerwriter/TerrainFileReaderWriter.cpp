#include "TerrainFileReaderWriter.h"
#include "LuaUtil.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <luabind/object.hpp>
#include <luabind/function.hpp>
#include <luabind/error.hpp>

TerrainFileReaderWriter::TerrainFileReaderWriter()
    : ReaderWriter<TerrainFile>()
{

}

TerrainFileReaderWriter::~TerrainFileReaderWriter()
{

}

bool TerrainFileReaderWriter::read(const QString &file, TerrainFile &object) const
{
    lua_State *state = 0;
    try {
        qDebug() << "TerrainFileReaderWriter::read - Reading " << file;
        luabind::object terrainTable;
        state = LuaUtil::openFile(file, &terrainTable);
        if(state == 0) {
            return false;
        }

        // Get file properties
        qDebug() << "TerrainFileReaderWriter::read - Reading file properties";

        // Get polygons
        QList<QPolygonF> polygons;
        for(luabind::iterator i(terrainTable), end; i != end; ++i) {
            luabind::object shape = (*i);
            QPolygonF polygon = LuaUtil::readShape(&shape);
            qDebug() << "TerrainFileReaderWriter::read - Adding polygon " << polygon;
            // Add polygon to polygon list.
            polygons.append(polygon);
        }

        // Set data onto object
        object.setPolygons(polygons);
    } catch(luabind::error &lbError) {
        qDebug() << "TerrainFileReaderWriter::read - Luabind Error " << LuaUtil::getErrorMessage(lbError.state());
        lua_close(lbError.state());
        return false;
    }
    lua_close(state);
    return true;
}

bool TerrainFileReaderWriter::write(const QString &file, const TerrainFile &object) const
{
    qDebug() << "TerrainFileReaderWriter::write - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "TerrainFileReaderWriter::write - Failed to open, returning false.";
        return false;
    }
    qDebug() << "TerrainFileReaderWriter::write - Successfully opened, writing data.";
    QTextStream stream(&diskFile);
    stream << "local Point = require(MATHPATH .. \'Point\')" << endl;
    stream << "local Shape = require(MATHPATH .. \'Shape\')" << endl << endl;
    stream << "return" << endl;
    stream << "{" << endl;
    for(int i = 0; i < object.getPolygons().size(); i++) {
        QPolygonF currentPolygon = object.getPolygons().at(i);
        stream << "    Shape:new(" << endl;
        for(int j = 0; j < currentPolygon.size(); j++) {
            QPointF currentPoint = currentPolygon.at(j);
            stream << "              Point:new(" << (int)currentPoint.x() << ", " << (int)currentPoint.y() << ")";
            if(j < currentPolygon.size() - 1) {
                stream << ",";
            }
            stream << endl;
        }
        stream << "             )";
        if(i < object.getPolygons().size() - 1) {
            stream << ",";
        }
        stream << endl;
    }
    stream << "}";
    qDebug() << "TerrainFileReaderWriter::write - Returning true.";
    return true;
}

bool TerrainFileReaderWriter::createDefaultFile(const QString &path) const
{
    qDebug() << "TerrainFileReaderWriter::createDefaultFile - Opening " << path;
    QFile diskFile(path);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "TerrainFileReaderWriter::createDefaultFile - Failed to open, returning false.";
        return false;
    }
    qDebug() << "TerrainFileReaderWriter::createDefaultFile - Successfully opened, writing data.";
    QTextStream stream(&diskFile);
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "}";
    qDebug() << "TerrainFileReaderWriter::createDefaultFile - Returning true.";
    return true;
}
