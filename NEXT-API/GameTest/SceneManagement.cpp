#include "stdafx.h"
#include "SceneManagement.h"

SceneManagement::SceneManagement()
{
	player = new Player(PLAYER_DEFAULT, std::vector<Vector2*>());
	LoadLevel(INTRO, new std::vector<std::string>());
	//LoadLevel(MAP_1);
}

void SceneManagement::LoadLevel(SCENE_LEVEL_TYPE id, std::vector<std::string>* msgs)
{
	if (activeType == INTRO || activeType == END)
	{
		//Resets the player stats and maps after coming from the end screen

		for (auto map : loadedMaps)
		{			
			if (id == MAP_1 && map->Map_Type == MAP_1)
			{
				map->ResetMap();
				map->CreateGrid(16, 16);
			}
			else if (id == MAP_2 && map->Map_Type == MAP_2)
			{
				map->ResetMap();
				map->CreateGrid(8, 8);
			}
		}
		player->ResetPlayer();
	}

	activeType = id;
	currentDelay = inputDelay;

	if ((id == INTRO || id == PAUSE) || id == END)
	{
		for (int s = 0; s < loadedScenes.size(); s++)
		{
			if (loadedScenes[s]->Scene_Type == (SCENE_LEVEL_TYPE)id)
			{
				//Opens a map
				loadedScenes[s]->SetSceneString(msgs);
				activeLevel = Vector2(0, s);
				return;
			}
		}

		activeLevel = Vector2(0, loadedScenes.size());
		loadedScenes.push_back(new Scene(id, msgs));
	}
	else
	{
		for (int m = 0; m < loadedMaps.size(); m++)
		{
			if (loadedMaps[m]->Map_Type == (SCENE_LEVEL_TYPE)id)
			{
				//Opens a map
				
				activeLevel = Vector2(1, m);
				player->SetBombSpawnablePos(loadedMaps[m]->emptyGridPoints);
				return;
			}
		}

		activeLevel = Vector2(1, loadedMaps.size());

		if ((SCENE_LEVEL_TYPE)id == MAP_1)
		{
			Map1* newMap1 = new Map1();
			newMap1->CreateGrid(16, 16);
			loadedMaps.push_back(newMap1);
		}
		else if ((SCENE_LEVEL_TYPE)id == MAP_2)
		{
			SmallMap* newSmallMap = new SmallMap();
			newSmallMap->CreateGrid(8, 8);
			loadedMaps.push_back(newSmallMap);
		}

		player->SetBombSpawnablePos(loadedMaps[loadedMaps.size()-1]->emptyGridPoints);


		//For future expansion of implementing N number of map levels
		// 
		//for (int m = 0; m < loadedMaps.size(); m++)
		//{
		//	if (loadedMaps[m]->Map_Type == (SCENE_LEVEL_TYPE)id)
		//	{
		//		//Opens a map
		//		loadedMaps[m]->ResetMap();
		//		activeLevel = Vector2(1, m);
		//		return;
		//	}
		//}
		//
		//activeLevel = Vector2(1, loadedMaps.size());
		//loadedMaps.push_back(new Map1(id));
	}
}

void SceneManagement::UpdateSceneComponents(float deltaTime)
{
	UpdateInput(deltaTime);

	if (activeLevel.x == 1) //Game Map Levels
	{
		CollisionChecks();

		if (loadedMaps[activeLevel.y] != nullptr)
		{
			loadedMaps[activeLevel.y]->Update(deltaTime);
		}
		player->UpdatePlayerElements(deltaTime);

		if (player->isOutOfLife)
		{
			//Pass player score to end screen
			std::vector<std::string>* data = new std::vector<std::string>();

			data->push_back("Enemies Killed: " + std::to_string(player->GetPlayerStatistics().EnemyKills));
			data->push_back("Time Survived: " + std::to_string((int)roundf(player->GetPlayerStatistics().timeElapsed)) + 's');
			LoadLevel(END, data);
		}
	}	
}

void SceneManagement::UpdateInput(float deltaTime)
{
	//Game Controls
	if (activeType == INTRO) //Intro screen controls
	{
		if (App::IsKeyPressed(VK_SPACE))
		{
			LoadLevel(MAP_1, new std::vector<std::string>());
		}
	}
	else if (activeType == PAUSE)
	{
		if (currentDelay <= 0.0f)
		{
			if (App::IsKeyPressed(VK_LSHIFT))
			{
				LoadLevel(MAP_1, new std::vector<std::string>());
			}
		}
	}
	else if (activeType == END)
	{
		if (App::IsKeyPressed(VK_LSHIFT))
		{
			LoadLevel(INTRO, new std::vector<std::string>());
		}
	}
	else
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

		if (currentDelay <= 0.0f)
		{
			if (App::IsKeyPressed(VK_SPACE))
			{
				if (player->PlaceBomb(0)) currentDelay = inputDelay;
			}

			if (App::IsKeyPressed(VK_LSHIFT))
			{
				LoadLevel(PAUSE, new std::vector<std::string>());
			}

			if (App::IsKeyPressed(VK_RSHIFT))
			{
				for (auto map : loadedMaps)
				{
					if (map->Map_Type == activeType)
					{
						isDebug = !isDebug;
						player->ShowPlayerDebugCollider(isDebug);
						map->DrawDebugElements(isDebug);
						currentDelay = inputDelay;
					}
				}
			}
		}
	}

	(currentDelay <= 0.0f) ? currentDelay = 0.0f : currentDelay -= deltaTime * 0.001f;

	//if (currentDelay <= 0.0f)
	//{
	//	currentDelay = 0.0f;
	//
	//	
	//
	//	//if (activeLevel.x == 0)
	//	//{
	//	//	if (activeType == INTRO) //Intro screen controls
	//	//	{
	//	//		if (App::IsKeyPressed(VK_SPACE))
	//	//		{
	//	//			LoadLevel(MAP_1, new std::vector<std::string>());
	//	//		}
	//	//	}
	//	//
	//	//	if (activeType == PAUSE)
	//	//	{
	//	//		if (App::IsKeyPressed(VK_LSHIFT))
	//	//		{
	//	//			LoadLevel(MAP_1, new std::vector<std::string>());
	//	//		}
	//	//	}
	//	//
	//	//	if (activeType == END)
	//	//	{
	//	//
	//	//	}
	//	//}
	//}
	//else
	//{
	//	currentDelay-=deltaTime*0.001f;
	//}

	//if (activeLevel.x == 1)
	//{
	//	//Player Movements
	//	if ((App::GetController().GetLeftThumbStickX() != 0.0f) || (App::GetController().GetLeftThumbStickY() != 0.0f))
	//	{
	//		if (App::GetController().GetLeftThumbStickX() > 0.5f)
	//		{
	//			player->Move(MOVE_RIGHT);
	//		}
	//		else if (App::GetController().GetLeftThumbStickX() < -0.5f)
	//		{
	//			player->Move(MOVE_LEFT);
	//		}
	//
	//		if (App::GetController().GetLeftThumbStickY() > 0.5f)
	//		{
	//			player->Move(MOVE_TOP);
	//		}
	//		else if (App::GetController().GetLeftThumbStickY() < -0.5f)
	//		{
	//			player->Move(MOVE_DOWN);
	//		}
	//	}
	//	else
	//	{
	//		player->Move(MOVE_NONE);
	//	}
	//
	//	if (currentDelay <= 0.0f)
	//	{
	//		if (App::IsKeyPressed(VK_SPACE))
	//		{
	//			player->PlaceBomb(0);
	//			currentDelay = inputDelay;
	//		}
	//
	//		if (App::IsKeyPressed(VK_LSHIFT))
	//		{
	//			LoadLevel(PAUSE, new std::vector<std::string>());
	//		}
	//	}
	//}
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
			if (wall->isActive)
			{
				if (CollisionManager::instance().hasHitAABB(player, wall))
				{
					if (wall->BlockType == TELEPORT)
					{
						bool mapFound = false;

						for (int m = 0; m < loadedMaps.size(); m++)
						{
							if (loadedMaps[m]->Map_Type != activeType)
							{
								//LoadLevel(map->Map_Type, {});
								mapFound = true;
								LoadLevel(loadedMaps[m]->Map_Type, new std::vector<std::string>());
								m += loadedMaps.size();
							}
						}

						if (!mapFound) LoadLevel(MAP_2, new std::vector<std::string>());
						//For future improvements, use teleport class that will include a link to the connected place
					}
					else if (wall->BlockType == DESTRUCTIBLE_LOOT)
					{
						wall->isActive = false;
						player->LootCrateCollected(wall);
					}
					else
					{
						player->PlayerTouchedWall(wall);
					}
				}
			}
		}

		//Check between player and pickups
		for (auto pickups : loadedMaps[activeLevel.y]->GetMapPickUpItems())
		{
			if (pickups->isActive)
			{
				if (CollisionManager::instance().hasHitAABB(player, pickups))
				{
					pickups->isActive = false;
					player->PickUpItemCollected(pickups);
				}
			}
		}

		//Check between player and enemies
		for (auto enemy : loadedMaps[activeLevel.y]->GetMapEnemies())
		{
			if (enemy->isActive)
			{
				if (CollisionManager::instance().hasHitAABB(player, enemy))
				{
					player->PlayerDied();
				}
			}
		}

		//Check between enemies and walls
		for (auto enemy : loadedMaps[activeLevel.y]->GetMapEnemies())
		{
			if (enemy->isActive)
			{
				for (auto wall : loadedMaps[activeLevel.y]->GetMapWalls())
				{
					if (wall->isActive)
					{
						if (CollisionManager::instance().hasHitAABB(enemy, wall))
						{
							enemy->EnemyTouchedWall(wall);
						}
					}
				}
			}
		}

		//Check between the bomb and player/enemies
		for (auto bomb : player->GetPlayerBombs())
		{
			if (bomb->isActive && bomb->Exploded)
			{
				for (auto arm : bomb->GetBombArms())
				{
					if (arm->isActive)
					{
						if (CollisionManager::instance().hasHitAABB(player, arm))
						{
							player->PlayerDied();
						}

						for (auto enemy : loadedMaps[activeLevel.y]->GetMapEnemies())
						{
							if (enemy->isActive)
							{
								if (CollisionManager::instance().hasHitAABB(arm, enemy))
								{
									player->EnemyKilled(enemy);
									enemy->ExplosionDamage(1);
								}
							}
						}
					}
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
