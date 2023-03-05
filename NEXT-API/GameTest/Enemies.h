#pragma once
#include "GameObject.h"
#include "AI.h"

//Enemy Stats
class EnemyStat
{
	//Default value
	int HealthAmount = 1;
	int BombCount = 100;
	int XP_reward = 10;
};

class WallBlock;
//Enemy class
class Enemies : public GameObject
{
public:
	Enemies();
	Enemies(int id, std::vector<Vector2*> ai_path); //ID for different types of enemies
	~Enemies() {}

	void ExplosionDamage(int hp_damage);//damage caused by player's bomb(s)
	void EnemyDropTraps();//For the more "intelligent" enemies to attack back

	void UpdateEnemy(float deltaTime);

	void EnemyTouchedWall(WallBlock* wall);

	AI* enemyAI;

private:
	Vector2 targetPosition;
	const int enemyID;
	EnemyStat EnemyStatistics;
};