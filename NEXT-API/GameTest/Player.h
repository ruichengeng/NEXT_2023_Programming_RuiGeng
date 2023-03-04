#pragma once
#include "Bomb.h"

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
	void CreateBombPool(int count);
	//void ReturnBomb(Bomb* b);
	void UpdatePlayerElements(float deltaTime); //For player and bombs

private:
	std::vector<Bomb*> bombPool;
};