#pragma once
#include "GameObject.h"

//Enemy Stats
class EnemyStat
{
	//Default value
	int HealthAmount = 1;
	int BombCount = 100;
	int XP_reward = 10;
};

//Enemy class
class Enemies : public GameObject
{
public:
	Enemies();
	Enemies(int id); //ID for different types of enemies
	~Enemies() {}

	void ExplosionDamage(int hp_damage);//damage caused by player's bomb(s)
	void EnemyDropTraps();//For the more "intelligent" enemies to attack back

private:
	Vector2 targetPosition;
	const int enemyID;
	EnemyStat EnemyStatistics;
};