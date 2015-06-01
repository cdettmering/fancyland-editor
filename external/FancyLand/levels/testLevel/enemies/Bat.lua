local Point = require(MATHPATH .. 'Point')
local Shape = require(MATHPATH .. 'Shape')
local Body = require(PHYSICSPATH .. 'Body')
local BodyPart = require(PHYSICSPATH .. 'BodyPart')
local GraphicUtility = require(GRAPHICSPATH .. 'GraphicUtility')

local x = math.pi
local function _update(base, dt)
    x = x + math.pi * dt
    base:actor():body():rotate(x)
end

local function _draw(base)
    GraphicUtility.drawActor(base:actor())
end

local function _onClick(base)
    base:actor()._alive = false
end

local function _onCollison(base, body1, body2, intersections)
end

return
{
    sprite = 'bat.png',
    body = Body:new(
               BODYTYPE_ENEMY,
               BodyPart:new(
                  'BatWing',
                   Shape:new(
                       Point:new(0, 0),
                       Point:new(100, 0),
                       Point:new(100, 51),
                       Point:new(0, 51))
                       )),
    type = 'Bat',
    update = _update,
    draw = _draw,
    onClick = _onClick,
    onCollision = _onCollision
}
