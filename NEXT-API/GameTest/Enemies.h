#pragma once
#include "GameObject.h"

class Enemies : public GameObject
{
public:
	Enemies();
	Enemies(int id); //Different types of enemies
	~Enemies() {}

	void ExplosionDamage(int hp_damage);
	void EnemyDropTraps();

private:
	Vector2 targetPosition;
	const int enemyID;
};