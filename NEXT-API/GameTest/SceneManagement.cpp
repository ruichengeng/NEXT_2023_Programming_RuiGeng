#include "stdafx.h"
#include "SceneManagement.h"

SceneManagement::SceneManagement()
{
	player = new Player();
	//LoadLevel(INTRO);
	LoadLevel(MAP_1);
}

void SceneManagement::LoadLevel(SCENE_LEVEL_TYPE id)
{
	for (auto level : loadedMaps)
	{
		if (level->Map_Type == (SCENE_LEVEL_TYPE)id)
		{
			//Opens a map
			
			return;
		}
	}

	activeLevel = loadedMaps.size();
	loadedMaps.push_back(new Map(id));
}

void SceneManagement::UpdateSceneComponents(float deltaTime)
{
	UpdateInput();
	CollisionChecks();

	if (activeLevel != -1 && loadedMaps[activeLevel] != nullptr)
	{
		loadedMaps[activeLevel]->Update(deltaTime);
	}
	
	player->UpdatePlayerElements(deltaTime);
}

void SceneManagement::UpdateInput()
{
	if ((App::GetController().GetLeftThumbStickX() != 0.0f) || (App::GetController().GetLeftThumbStickY() != 0.0f))
	{
		if (App::GetController().GetLeftThumbStickX() > 0.5f)
		{
			player->Move(MOVE_RIGHT);
		}
		else if (App::GetController().GetLeftThumbStickX() < -0.5f)
		{
			player->Move(MOVE_LEFT);
		}

		if (App::GetController().GetLeftThumbStickY() > 0.5f)
		{
			player->Move(MOVE_TOP);
		}
		else if (App::GetController().GetLeftThumbStickY() < -0.5f)
		{
			player->Move(MOVE_DOWN);
		}
	}
	else
	{
		player->Move(MOVE_NONE);
	}

	if (App::IsKeyPressed(VK_SPACE))
	{
		player->PlaceBomb(0);
	}
}

void SceneManagement::Render()
{
	if (activeLevel != -1 && loadedMaps[activeLevel] != nullptr)
	{
		loadedMaps[activeLevel]->Render();
	}

	player->RenderPlayerElements();
}

void SceneManagement::CollisionChecks()
{
	//Check between player and impassable walls
	for (auto wall : loadedMaps[activeLevel]->GetMapWalls())
	{
		if (CollisionManager::instance().hasHitAABB(player, wall))
		{
			player->PlayerTouchedWall(wall);
		}
	}

	//Check between player and enemies
	for (auto enemy : loadedMaps[activeLevel]->GetMapEnemies())
	{
		if (CollisionManager::instance().hasHitAABB(player, enemy))
		{
			player->PlayerDied();
		}
	}

	//Check between enemies and walls
	for (auto enemy : loadedMaps[activeLevel]->GetMapEnemies())
	{
		for (auto wall : loadedMaps[activeLevel]->GetMapWalls())
		{
			if (CollisionManager::instance().hasHitAABB(enemy, wall))
			{
				enemy->EnemyTouchedWall(wall);
			}
		}
	}

	//Check between enemies and enemies
	//for (int e1 = 0; e1 < gameMap->GetMapEnemies().size(); e1++)
	//{
	//	for (int e2 = e1 + 1; e2 < gameMap->GetMapEnemies().size(); e2++)
	//	{
	//		if (CollisionManager::instance().hasHitAABB(gameMap->GetMapEnemies()[e1], gameMap->GetMapEnemies()[e2]))
	//		{
	//
	//		}
	//	}
	//}

	//Check between enemies and bomb explosions
}
