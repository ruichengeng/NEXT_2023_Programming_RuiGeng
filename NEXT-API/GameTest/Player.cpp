#include "stdafx.h"
#include "Player.h"
#include "WallBlock.h"
#include "SceneManagement.h"
#include "Enemies.h"

Player::Player():Player(0, std::vector<Vector2*>()) {}

Player::Player(int id, std::vector<Vector2*> ai_path):GameObject(24.0f), potentialBombSpawnPos(ai_path), allEnemiesKilled(std::vector<Enemies*>())
{
	//For character selection, the id can be added to the end of the name. I.e: Player0, Player1, etc
	CreateGOSprite(".\\Art\\NeoEarlyBomberman.bmp", 7, 4, 430.0f, 512.0f, 1.0f);
	CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6 });
	CreateGOAnimation(ANIM_RIGHT, 1.0f / 15.0f, { 7,8,9,10,11,12,13 });
	CreateGOAnimation(ANIM_FORWARDS, 1.0f / 15.0f, { 14,15,16,17,18,19,20 });
	CreateGOAnimation(ANIM_LEFT, 1.0f / 15.0f, { 21,22,23,24,25,26,27 });

	initialPos = Vector2(430.0f, 512.0f);
	ResetPlayer();
}

void Player::PlaceBomb(int bombType)
{
	if ((currentSpawnCoolDown == 0.0f) && (playerStatistics.BombCount > 0))
	{
		float x, y;
		GetSprite()->GetPosition(x, y);

		for (int a = 0; a < bombPool.size(); a++)
		{
			if (!bombPool[a]->Exploded && !bombPool[a]->isActive)
			{
				Vector2 spawnPos = FindBombLocation();

				if (spawnPos.x != -1 && spawnPos.y != -1)
				{
					bombPool[a]->SetBomb(spawnPos.x, spawnPos.y);
					//bombPool[a]->SetBomb(x, y);
					currentSpawnCoolDown = bombSpawnCoolDown;
					playerStatistics.BombCount--;
				}
				return;
			}
		}

		AddToBombPool(1, bombType);
		PlaceBomb(bombType);
	}
}

void Player::AddToBombPool(int count, int bombType)
{
	for (int b = 0; b < count; b++)
	{
		Bomb* newBomb = new Bomb(bombType, potentialBombSpawnPos);
		newBomb->isActive = false;
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
	AddToBombPool(10, 0);
	GetSprite()->SetPosition(initialPos.x, initialPos.y);
}

void Player::RenderUIComponents()
{
	std::string level = "Level: " + std::to_string(playerStatistics.CharacterLevel);
	std::string lives = "HP: " + std::to_string(playerStatistics.Lives);
	std::string bomb = "Bomb: " + std::to_string(playerStatistics.BombCount);
	std::string enemy = "Enemy Killed: " + std::to_string(playerStatistics.EnemyKills);
	std::string xp = "XP: " + std::to_string(playerStatistics.XP);
	std::string time = "Time: " + std::to_string((int)roundf(playerStatistics.timeElapsed)) + "s";
	App::Print(512, 700, level.c_str(), 0.0f, 0.0f, 0.0f);
	App::Print(512, 650, lives.c_str(), 0.0f, 0.0f, 0.0f);
	App::Print(512, 600, bomb.c_str(), 0.0f, 0.0f, 0.0f);
	App::Print(512, 550, enemy.c_str(), 0.0f, 0.0f, 0.0f);
	App::Print(512, 500, xp.c_str(), 0.0f, 0.0f, 0.0f);
	App::Print(512, 450, time.c_str(), 0.0f, 0.0f, 0.0f);
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
