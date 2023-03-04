#pragma once
#include "Bomb.h"

//Player Stats for health, bomb count, and other variables
class PlayerStat
{
public:
	//Default values, changeable within the player class constructor
	int CharacterLevel = 1; //Can level up to increase damage output, gain extra abilities, etc.
	int Lives = 3;
	int BombCount = 10;
	int EnemyKills = 0;
	int XP = 0;

	//Variables for the gameplay experience
	float timeElapsed = 0.0f;
};

//Player class, responsible for the character selection and behaviours
class Player : public GameObject
{
public:
	Player();
	//The below constructor is used for character select if the player has multiple options
	Player(int id);
	~Player() {}

	//Bomb object-pool functions
	void PlaceBomb(int bombType);
	void AddToBombPool(int count, int bombType);
	//void ReturnBomb(Bomb* b);
	void UpdatePlayerElements(float deltaTime); //For player and bombs
	void RenderPlayerElements();

private:
	void RenderUIComponents();

private:
	std::vector<Bomb*> bombPool;
	PlayerStat playerStatistics;
	float bombSpawnCoolDown = 0.5f;
	float currentSpawnCoolDown = 0.0f;
};