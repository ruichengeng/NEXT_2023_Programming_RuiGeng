#pragma once
#include "Bomb.h"

//Player Stats for health, bomb count, and other variables
class PlayerStat
{
public:
	//Default values, changeable within the player class constructor
	int CharacterLevel = 1; //Can level up to increase damage output, gain extra abilities, etc.
	int Lives = 1;
	int BombCount = 10;
	int EnemyKills = 0;
	int XP = 0;

	//Variables for the gameplay experience
	float timeElapsed = 0.0f;
};

class WallBlock;
class SceneManagement;
class Enemies;
class PickUp;

//Player class, responsible for the character selection and behaviours
class Player : public GameObject
{
public:
	Player();
	//The below constructor is used for character select if the player has multiple options
	Player(PLAYER_TYPES id, std::vector<Vector2*> ai_path);
	~Player() {}

	//Bomb object-pool and related functions
	bool PlaceBomb(int bombType);
	void AddToBombPool(int count, int bombType);
	//void ReturnBomb(Bomb* b);
	void UpdatePlayerElements(float deltaTime); //For player and bombs
	void RenderPlayerElements();
	std::vector<Bomb*> GetPlayerBombs();

	//Game Object Interactions
	void EnemyKilled(Enemies* enemy);
	void LootCrateCollected(WallBlock* crate);
	void PickUpItemCollected(PickUp* item);

	//Setting the empty spaces
	void SetBombSpawnablePos(std::vector<Vector2*> pos);

	//Wall Contact
	void PlayerTouchedWall(WallBlock* wall);

	//Player dying
	void PlayerDied();

	PlayerStat GetPlayerStatistics();
	bool isOutOfLife = false;

	//Reset Player
	void ResetPlayer();

	void ShowPlayerDebugCollider(bool draw);

	//Change Player Type
	void ChangePlayerType(PLAYER_TYPES type, bool isInitial = true);

private:
	void RenderUIComponents();
	Vector2 FindBombLocation();

private:
	Vector2 initialPos;
	std::vector<Bomb*> bombPool;
	PlayerStat playerStatistics;
	float bombSpawnCoolDown = 0.5f;
	float currentSpawnCoolDown = 0.0f;

	std::vector<Vector2*> potentialBombSpawnPos;
	std::vector<Enemies*> allEnemiesKilled;
	std::vector<WallBlock*> allLootCrates;
	std::vector<PickUp*> allItemsPickedUp;

	PLAYER_TYPES playerType;
};