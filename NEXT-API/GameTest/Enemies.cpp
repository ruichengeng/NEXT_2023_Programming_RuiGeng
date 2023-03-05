#include "stdafx.h"
#include "Enemies.h"
#include "WallBlock.h"
#include <iostream>

Enemies::Enemies():Enemies(0, std::vector<Vector2*>()){}

Enemies::Enemies(int id, std::vector<Vector2*> ai_path) : GameObject(), enemyID(id)
{
	CreateGOSprite(".\\Art\\Enemies.bmp", 13, 4, 445.0f, 210.0f, 1.0f);

	//Currently there are 4 different enemies
	//Within each of the switch's cases, a unique feature about that type of enemy can be added (expansions)
	switch (id)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}

	CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 10.0f, {13 * id, 13 * id + 1, 13 * id + 2});
	CreateGOAnimation(ANIM_RIGHT, 1.0f / 10.0f, { 13 * id + 3, 13 * id + 4, 13 * id + 5, 13 * id + 6 });
	CreateGOAnimation(ANIM_LEFT, 1.0f / 10.0f, { 13 * id + 7, 13 * id + 8, 13 * id + 9, 13 * id + 10 });
	CreateGOAnimation(ANIM_FORWARDS, 1.0f / 10.0f, { 13 * id + 11, 13 * id + 12 });

	enemyAI = new AI(this);
	//enemyAI->ai_Type = (AI_TYPES)id;
	enemyAI->ai_Type = PATROL;
	enemyAI->patrolDirection = MOVE_RIGHT;
	enemyAI->SetUpPath(ai_path);
}

void Enemies::ExplosionDamage(int hp_damage)
{
	///enemy hurt animation then dies
	
	//animation here aksjdhaildfhalksdhfkasjdhfkasdhfklahsdf

	
	isActive = false;
}

void Enemies::EnemyDropTraps()
{
}

void Enemies::UpdateEnemy(float deltaTime)
{
	enemyAI->UpdateAI(deltaTime);
	Update(deltaTime);
}

void Enemies::EnemyTouchedWall(WallBlock* wall)
{
	float wallX, wallY;
	wall->GetSprite()->GetPosition(wallX, wallY);

	float x, y;
	GetSprite()->GetPosition(x, y);

	if (abs(x - wallX) < abs(y - wallY))
	{
		GetSprite()->SetPosition(x, wallY + (wall->ObjectRadius + ObjectRadius) * ((abs(y - wallY)) / (y - wallY)));
	}
	else
	{
		GetSprite()->SetPosition(wallX + (wall->ObjectRadius + ObjectRadius) * ((abs(x - wallX)) / (x - wallX)), y);
	}
}