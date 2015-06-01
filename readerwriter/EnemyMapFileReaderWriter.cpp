#include "EnemyMapFileReaderWriter.h"
#include "LuaUtil.h"

#include <QFile>
#include <QDebug>

#include <luabind/object.hpp>
#include <luabind/function.hpp>
#include <luabind/error.hpp>

EnemyMapFileReaderWriter::EnemyMapFileReaderWriter()
    : ReaderWriter<EnemyMapFile>()
{

}

EnemyMapFileReaderWriter::~EnemyMapFileReaderWriter()
{

}

bool EnemyMapFileReaderWriter::read(const QString &file, EnemyMapFile &object) const
{
    lua_State *state = 0;
    try {
        qDebug() << "EnemyMapFileReaderWriter::read - Reading " << file;
        luabind::object enemyMapTable;
        state = LuaUtil::openFile(file, &enemyMapTable);
        if(state == 0) {
            return false;
        }

        // Get file properties
        qDebug() << "EnemyMapFileReaderWriter::read - Reading file properties";

        // Get the dictionary which maps enemy type to enemy implementation file.
        QMap<QString, QString> dictionary;
        for(luabind::iterator i(enemyMapTable["dictionary"]), end; i != end; ++i) {
            std::string type = luabind::object_cast<std::string>(i.key());
            std::string file = luabind::object_cast<std::string>(*i);
            qDebug() << "EnemyMapFileReaderWriter::read - Dictionary Entry (" << QString(type.c_str()) << ", " << QString(file.c_str()) << ")";
            dictionary.insert(QString(type.c_str()), QString(file.c_str()));
        }

        // Get the list of enemies
        QList<QPair<QPointF, QString> > enemies;
        for(luabind::iterator i(enemyMapTable["enemies"]), end; i != end; ++i) {
            // Get the position
            luabind::object position = (*i)["position"];
            QPointF point = LuaUtil::readPoint(&position);

            // Get the type
            std::string type = luabind::object_cast<std::string>((*i)["type"]);
            qDebug() << "EnemyMapFileReaderWriter::read - Enemy Entry (" << point << ", " << QString(type.c_str()) << ")";
            enemies.append(QPair<QPointF, QString>(point, QString(type.c_str())));
        }

        // Set data onto object
        qDebug() << "EnemyMapFileReaderWriter::read - Setting data into memory object";
        object.setDictionary(dictionary);
        object.setEnemies(enemies);
    } catch(luabind::error &lbError) {
        qDebug() << "EnemyMapFileReaderWriter::read - Luabind Error " << LuaUtil::getErrorMessage(lbError.state());
        lua_close(lbError.state());
        return false;
    }
    lua_close(state);
    return true;
}

bool EnemyMapFileReaderWriter::write(const QString &file, const EnemyMapFile &object) const
{
    qDebug() << "EnemyMapFileReaderWriter::write - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "EnemyMapFileReaderWriter::write - Failed to open, returning false." << file;
        return false;
    }
    qDebug() << "EnemyMapFileReaderWriter::write - Successfully opened, writing data." << file;
    QTextStream stream(&diskFile);
    stream << "local Point = require(MATHPATH .. \'Point\')" << endl << endl;
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "    dictionary = { ";

    int count = 0;
    QMapIterator<QString, QString> currentEntry(object.getDictionary());
    while(currentEntry.hasNext()) {
        currentEntry.next();
        stream << "[\'" << currentEntry.key() << "\'] = \'" << currentEntry.value() << "\'";
        if(count < object.getDictionary().size() - 1) {
            stream << ",";
        }
        stream << endl;
        count++;
    }
    stream << "                 }," << endl;
    stream << "    enemies = {" << endl;
    for(int i = 0; i < object.getEnemies().size(); i++) {
        QPair<QPointF, QString> pair = object.getEnemies().at(i);
        QPointF pos = pair.first;
        QString type = pair.second;
        stream << "                   {position = Point:new(" << (int)pos.x() << ", " << (int)pos.y() << "), ";
        stream << "type = \'" << type << "\'}";
        if(i < object.getEnemies().size() - 1) {
            stream << ",";
        }
        stream << endl;
    }
    stream << "              }" << endl;
    stream << "}" << endl;
    qDebug() << "EnemyMapFileReaderWriter::write - Returning true.";
    return true;
}

bool EnemyMapFileReaderWriter::createDefaultFile(const QString &file) const
{
    qDebug() << "EnemyMapFileReaderWriter::createDefaultFile - Opening " << file;
    QFile diskFile(file);
    if(!diskFile.open(QIODevice::WriteOnly)) {
        qDebug() << "EnemyMapFileReaderWriter::createDefaultFile - Failed to open, returning false." << file;
        return false;
    }
    qDebug() << "EnemyMapFileReaderWriter::createDefaultFile - Successfully opened, writing data." << file;
    QTextStream stream(&diskFile);
    stream << "return" << endl;
    stream << "{" << endl;
    stream << "    dictionary = { }," << endl;
    stream << "    enemies = { }" << endl;
    stream << "}" << endl;
    qDebug() << "EnemyMapFileReaderWriter::createDefaultFile - Returning true.";
    return true;
}
