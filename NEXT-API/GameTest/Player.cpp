#include "stdafx.h"
#include "Player.h"
#include "WallBlock.h"
#include "SceneManagement.h"
#include "Enemies.h"
#include "PickUp.h"

Player::Player():Player(PLAYER_DEFAULT, std::vector<Vector2*>()) {}

Player::Player(PLAYER_TYPES id, std::vector<Vector2*> ai_path):GameObject(24.0f), playerType(id), potentialBombSpawnPos(ai_path)//, allEnemiesKilled(std::vector<Enemies*>())
{
	ChangePlayerType(id);
	ResetPlayer();
}

bool Player::PlaceBomb(int bombType)
{
	if ((currentSpawnCoolDown == 0.0f) && (playerStatistics.BombCount > 0))
	{
		float x, y;
		bool hasAvailableBomb = true;
		GetSprite()->GetPosition(x, y);

		//For now we will create a new bomb game object each time
		//Optimized sorting and reuse is below

		//if (bombPool.size() != 0)
		//{
		//	if (!bombPool[bombPool.size() - 1]->Exploded && !bombPool[bombPool.size() - 1]->isActive)
		//	{
		//		Vector2 spawnPos = FindBombLocation();
		//
		//		if (spawnPos.x != -1 && spawnPos.y != -1)
		//		{
		//			bombPool[bombPool.size() - 1]->SetBomb(spawnPos.x, spawnPos.y);
		//			//bombPool[a]->SetBomb(x, y);
		//			currentSpawnCoolDown = bombSpawnCoolDown;
		//			playerStatistics.BombCount--;
		//		}
		//		return true;
		//	}
		//}


		//Object Pool Sorting - in testing

		for (int a = 0; a < bombPool.size(); a++)
		{
			if (!bombPool[a]->Exploded && !bombPool[a]->isActive)
			{
				Vector2 spawnPos = FindBombLocation();
		
				if (spawnPos.x != -1 && spawnPos.y != -1)
				{
					if (!bombPool[a]->hasUsed) //Important for reusing the bomb
					{
						bombPool[a]->SetBomb(spawnPos.x, spawnPos.y);
						//bombPool[a]->SetBomb(x, y);
						currentSpawnCoolDown = bombSpawnCoolDown;
						playerStatistics.BombCount--;
						return true;
					}
				}
			}
		}

		AddToBombPool(1, bombType);
		//PlaceBomb(bombType);
	}
	return false;
}

void Player::AddToBombPool(int count, int bombType)
{
	for (int b = 0; b < count; b++)
	{
		Bomb* newBomb = new Bomb(bombType, potentialBombSpawnPos);
		//newBomb->ResetBomb();
		bombPool.push_back(newBomb);
	}
}

void Player::UpdatePlayerElements(float deltaTime)
{
	playerStatistics.timeElapsed += deltaTime * 0.001f;
	Update(deltaTime);

	if (currentSpawnCoolDown > 0.0f)
	{
		currentSpawnCoolDown -= deltaTime * 0.001f;
	}
	else
	{
		currentSpawnCoolDown = 0.0f;
	}

	for (int i = 0; i < bombPool.size(); i++)
	{
		if (bombPool[i]->isActive) bombPool[i]->UpdateBombState(deltaTime);
	}
}

void Player::RenderPlayerElements()
{
	Render();

	for (int i = 0; i < bombPool.size(); i++)
	{
		if (bombPool[i]->isActive) bombPool[i]->RenderBomb();
	}

	RenderUIComponents();
}

std::vector<Bomb*> Player::GetPlayerBombs()
{
	return bombPool;
}

void Player::EnemyKilled(Enemies* enemy)
{
	for (auto e : allEnemiesKilled)
	{
		if (e == enemy)
		{
			return;
		}
	}

	allEnemiesKilled.push_back(enemy);
	playerStatistics.EnemyKills = allEnemiesKilled.size();
}

void Player::LootCrateCollected(WallBlock* crate)
{
	for (auto c : allLootCrates)
	{
		if (c == crate)
		{
			return;
		}
	}

	allLootCrates.push_back(crate);
	playerStatistics.XP = allLootCrates.size() * 50; //Temp value of 50, can be generalized
}

void Player::PickUpItemCollected(PickUp* item)
{
	for (auto p : allItemsPickedUp)
	{
		if (p == item)
		{
			return;
		}
	}

	switch (item->PickUp_Type)
	{
	case PICKUP_APPLE: //Change Player To Red
		ChangePlayerType(PLAYER_RED, false);
		break;
	case PICKUP_CHERRY: //Add 1 Life
		playerStatistics.Lives++;
		break;
	case PICKUP_KEY: //Change Player To Blue
		ChangePlayerType(PLAYER_BLUE, false);
		break;
	case PICKUP_PEAR: //Change Player To Default
		ChangePlayerType(PLAYER_DEFAULT, false);
		break;
	case PICKUP_STRAWBERRY: //Time Decrease by 10 seconds (can't be negative but the decrement value can be changed later)
		(playerStatistics.timeElapsed > 10.0f) ? playerStatistics.timeElapsed -= 10.0f : playerStatistics.timeElapsed = 0.0f;
		break;
	default:
		break;
	}

	allItemsPickedUp.push_back(item);
}

void Player::SetBombSpawnablePos(std::vector<Vector2*> pos)
{
	potentialBombSpawnPos = pos;
}

void Player::PlayerTouchedWall(WallBlock* wall)
{
	float wallX, wallY;
	wall->GetSprite()->GetPosition(wallX, wallY);

	float x, y;
	GetSprite()->GetPosition(x, y);

	if (abs(x - wallX) < abs(y - wallY))
	{
		GetSprite()->SetPosition(x, wallY + (wall->ObjectRadius + ObjectRadius)*((abs(y - wallY))/(y-wallY)));
	}
	else
	{
		GetSprite()->SetPosition(wallX + (wall->ObjectRadius + ObjectRadius)*((abs(x - wallX)) / (x - wallX)), y);
	}
}

void Player::PlayerDied()
{
	if (playerStatistics.Lives > 1)
	{
		playerStatistics.Lives--;
		GetSprite()->SetPosition(500.0f, 500.0f);
	}
	else
	{
		isOutOfLife = true;
	}
}

PlayerStat Player::GetPlayerStatistics()
{
	return playerStatistics;
}

void Player::ResetPlayer()
{
	playerStatistics = PlayerStat();
	isOutOfLife = false;

	bombPool.clear();
	//AddToBombPool(10, 0);
	GetSprite()->SetPosition(initialPos.x, initialPos.y);
}

void Player::ShowPlayerDebugCollider(bool draw)
{
	isDebug = draw;

	for (auto b : bombPool)
	{
		isDebug = draw;
	}
}

void Player::ChangePlayerType(PLAYER_TYPES type, bool isInitial)
{
	playerType = type;
	float x = 430.0f;
	float y = 512.0f;

	if (!isInitial)
	{
		GetSprite()->GetPosition(x, y);
	}
	else
	{
		initialPos = Vector2(x, y);
	}

	//For character selection and changes
	switch (playerType)
	{
	case PLAYER_DEFAULT:
		CreateGOSprite(".\\Art\\NeoEarlyBomberman.bmp", 7, 4, x, y, 1.0f);
		CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6 });
		CreateGOAnimation(ANIM_RIGHT, 1.0f / 15.0f, { 7,8,9,10,11,12,13 });
		CreateGOAnimation(ANIM_FORWARDS, 1.0f / 15.0f, { 14,15,16,17,18,19,20 });
		CreateGOAnimation(ANIM_LEFT, 1.0f / 15.0f, { 21,22,23,24,25,26,27 });
		break;
	case PLAYER_RED:
		CreateGOSprite(".\\Art\\player_red.bmp", 8, 1, x, y, 1.0f);
		CreateGOAnimation(ANIM_FORWARDS, 1.0f / 15.0f, { 6, 7 });
		CreateGOAnimation(ANIM_RIGHT, 1.0f / 15.0f, { 0, 1 });
		CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 15.0f, { 4, 5 });
		CreateGOAnimation(ANIM_LEFT, 1.0f / 15.0f, { 2, 3 });
		break;
	case PLAYER_BLUE:
		CreateGOSprite(".\\Art\\player_blue.bmp", 8, 1, x, y, 1.0f);
		CreateGOAnimation(ANIM_FORWARDS, 1.0f / 15.0f, { 6, 7 });
		CreateGOAnimation(ANIM_RIGHT, 1.0f / 15.0f, { 0, 1 });
		CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 15.0f, { 4, 5 });
		CreateGOAnimation(ANIM_LEFT, 1.0f / 15.0f, { 2, 3 });
		break;
	}
}

void Player::RenderUIComponents()
{
	std::string level = "Level: " + std::to_string(playerStatistics.CharacterLevel);
	std::string lives = "HP: " + std::to_string(playerStatistics.Lives);
	std::string bomb = "Bomb: " + std::to_string(playerStatistics.BombCount);
	std::string enemy = "Enemy Killed: " + std::to_string(playerStatistics.EnemyKills);
	std::string xp = "XP: " + std::to_string(playerStatistics.XP);
	std::string time = "Time: " + std::to_string((int)roundf(playerStatistics.timeElapsed)) + "s";
	App::Print(32, 900, level.c_str());
	App::Print(32, 875, lives.c_str());
	App::Print(32, 850, bomb.c_str());
	App::Print(32, 825, enemy.c_str());
	App::Print(32, 800, xp.c_str());
	App::Print(32, 775, time.c_str());
}

Vector2 Player::FindBombLocation()
{
	float playerX, playerY;
	GetSprite()->GetPosition(playerX, playerY);

	if (potentialBombSpawnPos.size() == 0)
	{
		return Vector2(-1, -1);
		//return Vector2(playerX, playerY);
	}
	else
	{
		for (auto pos : potentialBombSpawnPos)
		{
			if (CollisionManager::instance().hasHitAABB(Vector2(playerX + 16.0f, playerY + 32.0f), Vector2(pos->x, pos->y), 30.0f, 30.0f))
			{
				//Check if there is a bomb there already

				for (auto bomb : bombPool)
				{
					float tempX, tempY;
					bomb->GetSprite()->GetPosition(tempX, tempY);

					if (bomb->isActive)
					{
						if (CollisionManager::instance().hasHitAABB(Vector2(tempX, tempY), Vector2(pos->x, pos->y), 2.0f, 2.0f))
						{
							return Vector2(-1, -1);
						}
					}
				}

				return Vector2(pos->x, pos->y);
			}
		}

		return Vector2(-1, -1);
	}
}
