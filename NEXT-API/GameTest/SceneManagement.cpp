#include "stdafx.h"
#include "SceneManagement.h"

SceneManagement::SceneManagement()
{
	player = new Player();
	LoadLevel(INTRO);
	//LoadLevel(MAP_1);
}

void SceneManagement::LoadLevel(SCENE_LEVEL_TYPE id)
{
	activeType = id;

	if ((id == INTRO || id == PAUSE) || id == END)
	{
		for (auto scene : loadedScenes)
		{
			if (scene->Scene_Type == (SCENE_LEVEL_TYPE)id)
			{
				//Opens a map

				return;
			}
		}

		activeLevel = Vector2(0, loadedScenes.size());
		loadedScenes.push_back(new Scene(id));
	}
	else
	{
		for (auto level : loadedMaps)
		{
			if (level->Map_Type == (SCENE_LEVEL_TYPE)id)
			{
				//Opens a map

				return;
			}
		}

		activeLevel = Vector2(1, loadedMaps.size());
		loadedMaps.push_back(new Map(id));
	}
}

void SceneManagement::UpdateSceneComponents(float deltaTime)
{
	UpdateInput();
	CollisionChecks();

	if (activeLevel.x == 0) //Game Scenes
	{
		//if (loadedScenes[activeLevel.y] != nullptr)
		//{
		//	loadedScenes[activeLevel.y]->Update(deltaTime);
		//}
	}
	else if (activeLevel.x == 1) //Game Map Levels
	{
		if (loadedMaps[activeLevel.y] != nullptr)
		{
			loadedMaps[activeLevel.y]->Update(deltaTime);
		}
		player->UpdatePlayerElements(deltaTime);
	}	
}

void SceneManagement::UpdateInput()
{
	//Game Controls
	if (activeLevel.x == 0)
	{
		if (activeType == INTRO) //Intro screen controls
		{
			if (App::IsKeyPressed(VK_SPACE))
			{
				LoadLevel(MAP_1);
			}
		}
		
	}

	if (activeLevel.x == 1)
	{
		//Player Movements
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
}

void SceneManagement::Render()
{
	if (activeLevel.x == 0) //Game Scenes
	{
		if (loadedScenes[activeLevel.y] != nullptr)
		{
			loadedScenes[activeLevel.y]->Render();
		}
	}
	else if (activeLevel.x == 1) //Game Map Levels
	{
		if (loadedMaps[activeLevel.y] != nullptr)
		{
			loadedMaps[activeLevel.y]->Render();
		}

		player->RenderPlayerElements();
	}
}

void SceneManagement::CollisionChecks()
{
	if ((activeLevel.x == 1) && (loadedMaps[activeLevel.y] != nullptr))
	{
		//Check between player and impassable walls
		for (auto wall : loadedMaps[activeLevel.y]->GetMapWalls())
		{
			if (CollisionManager::instance().hasHitAABB(player, wall))
			{
				player->PlayerTouchedWall(wall);
			}
		}

		//Check between player and enemies
		for (auto enemy : loadedMaps[activeLevel.y]->GetMapEnemies())
		{
			if (CollisionManager::instance().hasHitAABB(player, enemy))
			{
				player->PlayerDied();
			}
		}

		//Check between enemies and walls
		for (auto enemy : loadedMaps[activeLevel.y]->GetMapEnemies())
		{
			for (auto wall : loadedMaps[activeLevel.y]->GetMapWalls())
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
	}
	
	//Check between enemies and bomb explosions
}
