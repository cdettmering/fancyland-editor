--- EnemyFile ---

-- Setup local access
local EnemyFile = {}
local EnemyFile_mt = {}
EnemyFile_mt.__index = EnemyFile

function EnemyFile:new(sprite, body, enemyType, update, draw, onClick, onCollision)
    local enemyFile = {}
    enemyFile.sprite = sprite
    enemyFile.body = body
    enemyFile.type = enemyType
    enemyFile.update = update
    enemyFile.draw = draw
    enemyFile.onClick = onClick
    enemyFile.onCollision = onCollision

    return setmetatable(enemyFile, EnemyFile_mt)
end

return EnemyFile
