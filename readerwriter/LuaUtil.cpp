#include "LuaUtil.h"

#include <QFile>
#include <QDebug>

#include <lua.hpp>

const QString LuaUtil::INCLUDE_POINT = "local Point = require(MATHPATH .. \'Point\')";
const QString LuaUtil::INCLUDE_SHAPE = "local Point = require(MATHPATH .. \'Shape\')";

lua_State * LuaUtil::openFile(const QString &file, luabind::object *object)
{
    if(!QFile::exists(file)) {
        qDebug() << "LuaUtil::openFile - File " << file << " does not exist";
        return 0;
    }

    // Open a new Lua state
    lua_State *state = luaL_newstate();
    luaL_openlibs(state);

    // Attach Luabind
    luabind::open(state);

    // Load FancyLand lua dependencies
    try {
        qDebug() << "LuaUtil::openFile - Loading dependencies";
        int error = luaL_loadfile(state, "external/FancyLand/lua/fancyland.lua");
        if(error) {
            qDebug() << "LuaUtil::openFile- Error code " << error << " when loading external/FancyLand/lua/fancyland.lua";
            lua_close(state);
            return 0;
        }
        luabind::object dependChunk(luabind::from_stack(state, -1));
        luabind::call_function<void>(dependChunk);
    } catch(luabind::error &lbError) {
        qDebug() << "LuaUtil::openFile - Luabind Error " << lbError.what();
        qDebug() << LuaUtil::getErrorMessage(state);
        lua_close(state);
        return 0;
    }

    // Load actual file
    try {
        qDebug() << "LuaUtil::openFile - Loading " << file;
        int error = luaL_loadfile(state, file.toStdString().c_str());
        if(error) {
            qDebug() << "LuaUtil::openFile- Error code " << error << " when loading " << file;
            lua_close(state);
            return 0;
        }
        luabind::object chunk(luabind::from_stack(state, -1));
        *object = luabind::call_function<luabind::object>(chunk);
    } catch(luabind::error &lbError) {
        qDebug() << "LuaUtil::openFile - Luabind Error " << lbError.what();
        qDebug() << LuaUtil::getErrorMessage(state);
        lua_close(state);
        return 0;
    }

    return state;
}

QString LuaUtil::getErrorMessage(lua_State *state)
{
    luabind::object error(luabind::from_stack(state, -1));
    std::string errorMessage = luabind::object_cast<std::string>(error);
    return QString(errorMessage.c_str());
}

QPolygonF LuaUtil::readShape(luabind::object *shapeObject)
{
    // Get the function name points from the Shape object.
    luabind::object pointsChunk = (*shapeObject)["points"];

    // Pass in the "self" parameter to the points function.
    luabind::object pointsTable = luabind::call_function<luabind::object>(pointsChunk, *shapeObject);
    QPolygonF polygon;

    // Iterate through each point on the Shape and add it to the polygon.
    for(luabind::iterator j(pointsTable), pEnd; j != pEnd; ++j) {
        luabind::object point = *j;
        polygon.append(LuaUtil::readPoint(&point));
    }

    return polygon;
}

QPointF LuaUtil::readPoint(luabind::object *pointObject)
{
    float x = luabind::object_cast<float>((*pointObject)["x"]);
    float y = luabind::object_cast<float>((*pointObject)["y"]);
    return QPointF(x, y);
}

BodyPart LuaUtil::readBodyPart(luabind::object *bodyPartObject)
{
    qDebug() << "LuaUtil::readBodyPart - Reading body part.";
    BodyPart part;
    luabind::object partTable = *bodyPartObject;

    // Get the name
    std::string name = luabind::object_cast<std::string>(partTable["_type"]);
    part.setName(QString(name.c_str()));
    qDebug() << "LuaUtil::readBodyPart - Name " << part.getName();

    // Get the shape
    luabind::object shapeTable = partTable["_shape"];
    part.setShape(LuaUtil::readShape(&shapeTable));
    qDebug() << "LuaUtil::readBodyPart - Shape " << part.getShape();

    qDebug() << "LuaUtil::readBodyPart - Returning body part";
    return part;
}

Body LuaUtil::readBody(luabind::object *bodyObject)
{
    qDebug() << "LuaUtil::readBody - Reading body.";
    Body body;
    luabind::object bodyTable = *bodyObject;

    // Get the type
    std::string type = luabind::object_cast<std::string>(bodyTable["_type"]);
    body.setType(QString(type.c_str()));
    qDebug() << "LuaUtil::readBody - Type " << body.getType();

    // Get the parts.
    luabind::object partsTable = bodyTable["parts"];
    for(luabind::iterator i(partsTable), end; i != end; ++i) {
        luabind::object partObject = *i;
        BodyPart part = LuaUtil::readBodyPart(&partObject);
        body.append(part);
    }

    qDebug() << "LuaUtil::readBody - Returning body.";
    return body;
}
