#include "LayerFileReaderWriter.h"
#include "LuaUtil.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <luabind/object.hpp>
#include <luabind/function.hpp>
#include <luabind/error.hpp>

LayerFileReaderWriter::LayerFileReaderWriter()
    : ReaderWriter<LayerFile>()
{

}

LayerFileReaderWriter::~LayerFileReaderWriter()
{

}

bool LayerFileReaderWriter::read(const QString &file, LayerFile &object) const
{
    lua_State *state = 0;
    try {
        qDebug() << "LayerFileReaderWriter::read - Reading " << file;
        luabind::object layerTable;
        state = LuaUtil::openFile(file, &layerTable);
        if(state == 0) {
            return false;
        }

        // Get file properties
        qDebug() << "LayerFileReaderWriter::read - Reading file properties";

        // Get speed
        float speed = luabind::object_cast<float>(layerTable["speed"]);
        qDebug() << "LayerFileReaderWriter::read - Speed " << speed;

        QStringList textures;
        luabind::object textureTable = layerTable["textures"];
        for(luabind::iterator i(textureTable), end; i != end; ++i) {
            std::string currentTexture = luabind::object_cast<std::string>(*i);
            qDebug() << "LayerFileReaderWriter::read - Texture " << QString(currentTexture.c_str());
            textures.append(QString(currentTexture.c_str()));
        }

        // Set data onto object
        object.setSpeed(speed);
        object.setTextures(textures);
    } catch(luabind::error &lbError) {
        qDebug() << "LayerFileReaderWriter::read - Luabind Error " << LuaUtil::getErrorMessage(lbError.state());
        lua_close(lbError.state());
        return false;
    }

    lua_close(state);
    return true;
}

bool LayerFileReaderWriter::write(const QString &file, const LayerFile &object) const
{
    qDebug() << "LayerFileReaderWriter::write - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "LayerFileReaderWriter::write - Failed to open, returning false.";
        return false;
    }
    qDebug() << "LayerFileReaderWriter::write - Successfully opened, writing data.";
    QTextStream stream(&diskFile);
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "    speed = " << object.getSpeed() << "," << endl;
    stream << "    textures = { ";
    for(int i = 0; i < object.getTextures().size(); i++) {
        stream << "\'" << object.getTextures().at(i) << "\'";
        if(i < object.getTextures().size() - 1) {
            stream << ",";
        }
    }
    stream << "}" << endl;
    stream << "}" << endl;
    qDebug() << "LayerFileReaderWriter::write - Returning true";
    return true;
}

bool LayerFileReaderWriter::createDefaultFile(const QString &file) const
{
    qDebug() << "LayerFileReaderWriter::createDefaultFile - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "LayerFileReaderWriter::createDefaultFile - Failed to open, returning false." << file;
        return false;
    }
    qDebug() << "LayerFileReaderWriter::createDefaultFile - Successfully opened, writing data." << file;
    QTextStream stream(&diskFile);
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "    speed = 1.0," << endl;
    stream << "    textures = { }";
    stream << "}" << endl;
    qDebug() << "LayerFileReaderWriter::createDefaultFile - Returning true." << file;
    return true;
}
