--- Shape ---

-- Setup local access
local Point = require(MATHPATH .. 'Point')
local LineSegment = require(MATHPATH .. 'LineSegment')
local BoundingBox = require(MATHPATH .. 'BoundingBox')
local MathUtil = require(MATHPATH .. 'MathUtil')
local pi = math.pi
local cosine = math.cos
local sine = math.sin
local assert = assert

local Shape = {}
local Shape_mt = {}
Shape_mt.__index = Shape

-- Clips angle to be between 0 and 2 pi.
-- param radians: The angle to clip (in radians).
-- return: The clipped angle
local function clipAngle(radians)
    while radians < 0 do
        radians = radians + (2 * pi)
    end

    while radians > (2 * pi) do
        radians = radians - (2 * pi)
    end
    
    return radians
end

-- Rotates point around origin by radians.
-- param point: The Point to rotate.
-- param radians: The amount to rotate by (in radians).
-- return: Rotated point.
local function rotatePoint(point, radians)
    local r = clipAngle(radians)

    -- rotate
    local x, y, _ = point:components()
    point.x = x * cosine(radians) - y * sine(r)
    point.y = x * sine(radians) + y * cosine(r)
    return point
end

-- Creates a new Shape
-- params: Variable number of Point objects, created by Point:new.
--         NOTE: The minimum number of points is 3.
function Shape:new(...)
    assert(arg.n > 2, 'Shape:new - Needs at least 3 Points')

    local shape = {}
    local points = {}
    shape.lines = {}
    shape.orientation = 0
    
    -- collect all of the points 
    local a = 1
    for i, v in ipairs(arg) do
        table.insert(points, v)
        a = a + 1
    end

    -- connect the first a - 1 points, where a = shape.points.size
    local c = 1
    for b = 1, (a - 2) do
        table.insert(shape.lines, LineSegment:new(points[b], points[b + 1]))
        c = c + 1
    end

    -- connect the last line
    table.insert(shape.lines, LineSegment:new(points[c], points[1]))

    return setmetatable(shape, Shape_mt)
end

-- Translates the shape to point.
-- param point: The Point to translate to.
function Shape:translate(point)
    local offset = point - self:center()
    -- move all lines
    for i, _ in ipairs(self.lines) do
        self.lines[i].p1 = self.lines[i].p1 + offset
        self.lines[i].p2 = self.lines[i].p2 + offset
    end
end

-- Rotates the Shape to radians.
-- param radians: The amount to rotate the shape clockwise. 
function Shape:rotate(radians)
    -- find out how many radians to rotate by
    local offset = radians - self.orientation
    local savePoint = self:center();

    -- move to origin
    self:translate(Point:new())

    -- rotate all lines
    for i, line in ipairs(self.lines) do
        -- rotate
        self.lines[i].p1 = rotatePoint(self.lines[i].p1, offset)
        self.lines[i].p2 = rotatePoint(self.lines[i].p2, offset)
    end

    -- move back
    self:translate(savePoint)
end

-- Gets the current Center Point of the Shape
function Shape:center()
    return MathUtil.averagePoints(self:points())
end

function Shape:boundingBox()
    return BoundingBox.fromShape(self)
end

function Shape:points()
    local pts = {}
    for _, line in ipairs(self.lines) do
        table.insert(pts, line:startPoint())
    end
    return pts
end

-- Checks if this Shape is intersecting shape.
-- param shape: The other Shape to check against this one.
-- return: If the two Shapes are intersecting a list of the intersection points is returned. Otherwise nil is returned.
function Shape:isIntersecting(shape)
    local intersectionPoints = {}
    for _, l1 in ipairs(self.lines) do
        for _, l2 in ipairs(shape.lines) do
            local point = l1:isIntersecting(l2)
            if point then
                table.insert(intersectionPoints, point)
            end
        end
    end
    if #intersectionPoints > 0 then
        return intersectionPoints
    end
    return nil
end

-- Checks if point is within this Shape
-- param point: The test point
-- return: True if the point is inside Shape, false otherwise
function Shape:isInside(point)
    -- make a line segment that starts on the outside and ends at the test point
    bb = self:boundingBox()
    local start = point - Point:new(bb:width() * 2, 0)
    local testSegment = LineSegment:new(start, point)
    
    local count = 0
    -- check all sides of the shape with my test segment
    for _, line in ipairs(self.lines) do
        if testSegment:isIntersecting(line) then
            count = count + 1
        end
    end

    -- if the number of intersections is even, then the point is outside
    if count % 2 == 0 then
        return false
    end
    return true    
end

local function toString(shape)
    local str = 'Shape[Lines: '
    for _, v in ipairs(shape.lines) do
        str = str .. tostring(v) .. ' '
    end
    str = str .. ']'
    return str
end

Shape_mt.__tostring = toString

return Shape
