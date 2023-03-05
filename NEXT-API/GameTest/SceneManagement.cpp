#include "stdafx.h"
#include "SceneManagement.h"

SceneManagement::SceneManagement()
{
	player = new Player(0);
	LoadLevel(INTRO, new std::vector<std::string>());
	//LoadLevel(MAP_1);
}

void SceneManagement::LoadLevel(SCENE_LEVEL_TYPE id, std::vector<std::string>* msgs)
{
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
		player->ResetPlayer();

		for (int m = 0; m < loadedMaps.size(); m++)
		{
			if (loadedMaps[m]->Map_Type == (SCENE_LEVEL_TYPE)id)
			{
				//Opens a map
				loadedMaps[m]->ResetMap();
				activeLevel = Vector2(1, m);
				return;
			}
		}

		activeLevel = Vector2(1, loadedMaps.size());

		if ((SCENE_LEVEL_TYPE)id == MAP_1)
		{
			loadedMaps.push_back(new Map1());
		}
		else if ((SCENE_LEVEL_TYPE)id == MAP_2)
		{
			loadedMaps.push_back(new SmallMap());
		}


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

	if (activeLevel.x == 0) //Game Scenes
	{
		if (activeType == END)
		{

		}
		//if (loadedScenes[activeLevel.y] != nullptr)
		//{
		//	loadedScenes[activeLevel.y]->Update(deltaTime);
		//}
	}
	else if (activeLevel.x == 1) //Game Map Levels
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
			data->push_back("Time Survived: " + std::to_string((int)roundf(player->GetPlayerStatistics().timeElapsed)));
			LoadLevel(END, data);
		}
	}	
}

void SceneManagement::UpdateInput(float deltaTime)
{
	//for (auto s : loadedScenes)
	//{
	//	if (s->Scene_Type == activeType)
	//	{
	//		
	//	}
	//}

	for (auto m : loadedMaps)
	{
		m->Update((m->Map_Type == activeType) ? deltaTime : 0.0f);
	}

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
				player->PlaceBomb(0);
				currentDelay = inputDelay;
			}

			if (App::IsKeyPressed(VK_LSHIFT))
			{
				LoadLevel(PAUSE, new std::vector<std::string>());
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
				else
				{
					player->PlayerTouchedWall(wall);
				}
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
