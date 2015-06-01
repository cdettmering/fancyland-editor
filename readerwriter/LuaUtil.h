#ifndef LUAUTIL_H
#define LUAUTIL_H

#include "datatype/BodyPart.h"
#include "datatype/Body.h"

#include <QString>
#include <QPolygonF>
#include <QPointF>

#include <luabind/object.hpp>
#include <luabind/function.hpp>
#include <luabind/error.hpp>

class LuaUtil
{
public:
    static lua_State * openFile(const QString &file, luabind::object *object);
    static QString getErrorMessage(lua_State *state);
    static QPolygonF readShape(luabind::object *shapeObject);
    static QPointF readPoint(luabind::object *pointObject);
    static BodyPart readBodyPart(luabind::object *bodyPartObject);
    static Body readBody(luabind::object *bodyObject);

    static const QString INCLUDE_POINT;
    static const QString INCLUDE_SHAPE;
};

#endif // LUAUTIL_H
