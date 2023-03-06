#include "stdafx.h"
#include "Enemies.h"
#include "WallBlock.h"
#include <iostream>

Enemies::Enemies():Enemies(0, std::vector<Vector2*>()){}

Enemies::Enemies(int id, std::vector<Vector2*> ai_path) : GameObject(), enemyID(id)
{
	if (id != ENEMY_PAC)
	{
		CreateGOSprite(".\\Art\\Enemies.bmp", 13, 4, 445.0f, 210.0f, 1.0f);

		CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 10.0f, { 13 * id, 13 * id + 1, 13 * id + 2 });
		CreateGOAnimation(ANIM_RIGHT, 1.0f / 10.0f, { 13 * id + 3, 13 * id + 4, 13 * id + 5, 13 * id + 6 });
		CreateGOAnimation(ANIM_LEFT, 1.0f / 10.0f, { 13 * id + 7, 13 * id + 8, 13 * id + 9, 13 * id + 10 });
		CreateGOAnimation(ANIM_FORWARDS, 1.0f / 10.0f, { 13 * id + 11, 13 * id + 12 });
	}
	else
	{
		CreateGOSprite(".\\Art\\enemy_pac.bmp", 4, 4, 445.0f, 210.0f, 1.0f);
		CreateGOAnimation(ANIM_FORWARDS, 1.0f / 15.0f, { 12, 13, 14, 15 });
		CreateGOAnimation(ANIM_RIGHT, 1.0f / 15.0f, { 0, 1, 2, 3 });
		CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 15.0f, { 8, 9, 10, 11 });
		CreateGOAnimation(ANIM_LEFT, 1.0f / 15.0f, { 4, 5, 6, 7 });
	}


	enemyAI = new AI(this);
	//enemyAI->ai_Type = (AI_TYPES)id;
	enemyAI->ai_Type = PATROL;
	enemyAI->patrolDirection = MOVE_TOP;
	enemyAI->SetUpPath(ai_path);
}

void Enemies::SetEnemyState(Vector2 newPos, MovementDirection dir, AI_TYPES type)
{
	GetSprite()->SetPosition(newPos.x, newPos.y);
	enemyAI->patrolDirection = dir;
	enemyAI->ai_Type = type;
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