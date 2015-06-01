--- Body ---

-- Setup local access
local Point = require(MATHPATH .. 'Point')
local MathUtil = require(MATHPATH .. 'MathUtil')
local BodyPart = require(PHYSICSPATH .. 'BodyPart')
local assert = assert

local Body = {}
local Body_mt = {}
Body_mt.__index = Body

-- Creates a new Body
-- param bodyType: String identifier for client use.
-- param ...: 1 or more BodyPart objects that make up the Body.
function Body:new(bodyType, ...)
    assert(arg.n > 0, 'Body:new - Needs at least 1 BodyPart')
    local body = {}
    body._velocity = Point:new()
    body._orientation = 0
    body._type = bodyType

    body.parts = {}
    for _, v in ipairs(arg) do
        table.insert(body.parts, v)
    end
    
    -- compute center position of the complex body
    local shapePoints = {}
    for _, part in ipairs(body.parts) do
        for _, p in ipairs(part:shape():points()) do
            table.insert(shapePoints, p)
        end
    end
    body._position = MathUtil.averagePoints(shapePoints)

    body._forces = {}

    return setmetatable(body, Body_mt)
end

-- Gets the type of this Body
-- return: String representing the type of Body.
function Body:type()
    return self._type
end                                 

function Body:forces()
    return self._forces
end

-- Gets the position of the body
-- return: Point object that represents the position of the body (center).
function Body:position()
    return self._position
end

-- Moves this Body to point.
-- param point: The Point to move the Body to.
function Body:move(point)
    -- Move the body as a unit, each part must move by offset
    local offset = point - self._position
    for _, part in ipairs(self.parts) do
        part:shape():translate(part:shape():center() + offset)
    end
    self._position = point
end

-- Gets the velocity of this Body
-- return: Point object that represents the velocity of this Body.
function Body:velocity()
    return self._velocity
end

-- Applies a force to this Body
-- param force: The force to apply
function Body:applyForce(force)
    table.insert(self._forces, force)
end

-- Applies an impulse to this Body
-- param force: The force to apply.
function Body:applyImpulse(force)
    self._velocity = self._velocity + force
end

-- Gets the orientation of this Body
-- return: Radians from the line (0, 1, 0)
function Body:orientation()
    return self._orientation
end

-- Rotates the body to radians from the line (0, 1, 0).
-- param radians: The theta of rotation from the line (0, 1, 0) in radians.
function Body:rotate(radians)
    -- TODO: Rotate
    self._orientation = radians
end


-- Checks if body is intersecting this Body
-- return: If the bodies are intersecting a list is returned with each element defined as:
-- {part1, part2, points}, where part1 and part2 are the intersecting BodyParts and
-- points is a list of Point objects that represent all points of intersection.
function Body:isIntersecting(body)
    local intersectionList = nil
    for _, part1 in ipairs(self.parts) do
        for _, part2 in ipairs(body.parts) do
            local points = part1:shape():isIntersecting(part2:shape())
            if points then
                if intersectoinList == nil then
                    intersectionList = {}
                end
                local element = {}
                element.part1 = part1
                element.part2 = part2
                element.points = points
                table.insert(intersectionList, element)
            end
        end
    end
    return intersectionList
end

function Body:isInside(point)
    for _, part in ipairs(self.parts) do
        if part:shape():isInside(point) then
            return true
        end
    end
    return false
end

local function toString(body)
    local str = 'Body['
    for _, part in ipairs(body.parts) do
        str = str .. tostring(part) .. ' '
    end
    str = str .. ']'
    return str
end

Body_mt.__tostring = toString

return Body
