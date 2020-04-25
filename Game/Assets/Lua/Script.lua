
function CreateEnemy()
	local enemyID = g_logic.CreateGameUnit("Assets/XML/TestEnemyUnit.xml")
	g_logic.CreateEnemyView(enemyID)
	g_logic.Log(string.format("Game Unit - %d (Enemy) Created Successfully!", enemyID))
	g_logic.Log(string.format("Enemy View for ID - %d Created Successfully!", enemyID))
end

function PlayMusic(fileName)
	g_logic.PlayMusic(fileName)
	g_logic.Log(string.format("Playing Music - %s!", fileName))
end

function PlaySound(fileName)
	g_logic.PlaySoundChunk(fileName)
	g_logic.Log(string.format("Playing Sound Chunk - %s!", fileName))
end

function Move(unitID, dx, dy)
	local transform = g_logic.GameUnits[unitID].TransformComponent
	transform.Move(transform.this, dx, dy)
end

function PlayerMoveRight(delta)
	local transform = g_logic.GameUnits[g_playerID].TransformComponent
	transform.Move(transform.this, delta * kFrameRate, 0)
end

function PlayerMoveLeft(delta)
	local transform = g_logic.GameUnits[g_playerID].TransformComponent
	transform.Move(transform.this, -(delta * kFrameRate), 0)
end

function PlayerMoveUp(delta)
	local transform = g_logic.GameUnits[g_playerID].TransformComponent
	transform.Move(transform.this, 0, -(delta * kFrameRate))
end

function PlayerMoveDown(delta)
	local transform = g_logic.GameUnits[g_playerID].TransformComponent
	transform.Move(transform.this, 0, delta * kFrameRate)
end

g_playerID = g_logic.CreateGameUnit("Assets/XML/TestPlayerUnit.xml")
g_logic.CreatePlayerView(g_playerID)
g_logic.Log(string.format("Game Unit - %d (Player) Created Successfully!", g_playerID))
g_logic.Log(string.format("Player View for ID - %d Created Successfully!", g_playerID))

CreateEnemy()

kFrameRate = 60

