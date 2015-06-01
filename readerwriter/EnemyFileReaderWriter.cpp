#include "EnemyFileReaderWriter.h"
#include "LuaUtil.h"

#include <QFile>
#include <QDebug>

#include <luabind/object.hpp>
#include <luabind/function.hpp>
#include <luabind/error.hpp>

EnemyFileReaderWriter::EnemyFileReaderWriter()
    : ReaderWriter<EnemyFile>()
{

}

EnemyFileReaderWriter::~EnemyFileReaderWriter()
{

}

bool EnemyFileReaderWriter::read(const QString &file, EnemyFile &object) const
{
    lua_State *state = 0;
    try {
        qDebug() << "EnemyFileReaderWriter::read - Reading " << file;
        luabind::object enemyTable;
        state = LuaUtil::openFile(file, &enemyTable);
        if(state == 0) {
            return false;
        }

        // Get file properties
        qDebug() << "EnemyFileReaderWriter::read - Reading file properties";

        // Get type
        std::string type = luabind::object_cast<std::string>(enemyTable["type"]);
        qDebug() << "EnemyFileReaderWriter::read - Type " << QString(type.c_str());

        // Get sprite
        std::string sprite = luabind::object_cast<std::string>(enemyTable["sprite"]);
        qDebug() << "EnemyFileReaderWriter::read - SpriteFile " << QString(sprite.c_str());

        //Get body
        luabind::object bodyTable = enemyTable["body"];
        Body body = LuaUtil::readBody(&bodyTable);
        //qDebug() << "EnemyFileReaderWriter::read - Body " << body;

        // Set data onto object
        qDebug() << "EnemyFileReaderWriter::read - Setting data into memory object";
        object.setType(QString(type.c_str()));
        object.setSpriteFile(QString(sprite.c_str()));
        object.setBody(body);
    } catch(luabind::error &lbError) {
        qDebug() << "EnemyFileReaderWriter::read - Luabind Error " << LuaUtil::getErrorMessage(lbError.state());
        lua_close(lbError.state());
        return false;
    }
    lua_close(state);
    return true;
}

bool EnemyFileReaderWriter::write(const QString &file, const EnemyFile &object) const
{
    qDebug() << "EnemyFileReaderWriter::write - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "EnemyFileReaderWriter::write - Failed to open, returning false." << file;
        return false;
    }
    qDebug() << "EnemyFileReaderWriter::write - Successfully opened, writing data." << file;
    QTextStream stream(&diskFile);
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "    sprite = " << object.getSpriteFile() << "," << endl;
    stream << "    body = Body:new(" << endl;
    stream << "              " << object.getBody().getType() << "," << endl;
    for(int i = 0; i < object.getBody().size(); i++) {
        BodyPart part = object.getBody().at(i);
        stream << "        BodyPart:new(" << endl;
        stream << "           \'" << part.getName() << "\'," << endl;
        stream << "             Shape:new(" << endl;
        for(int j = 0; j < part.getShape().size(); j++) {
            QPointF point = part.getShape().at(i);
            stream << "            Point:new(" << point.x() << ", " << point.y() << ")";
            if(j < part.getShape().size() - 1) {
                stream << ",";
            }
            stream << endl;
        }
        stream << "            ))";
        if(i < object.getBody().size() - 1) {
            stream << ",";
        }
        stream << endl;
    }
    stream << "               )," << endl;
    stream << "type = \'" << object.getType() << "\'" << endl;
    stream << "}" << endl;
    qDebug() << "EnemyFileReaderWriter::write - Returning True" << file;
    return true;
}

bool EnemyFileReaderWriter::createDefaultFile(const QString &path) const
{
    return true;
}
