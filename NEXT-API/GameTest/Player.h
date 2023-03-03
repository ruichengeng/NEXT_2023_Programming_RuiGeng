#pragma once
#include "GameObject.h"

//Player class, responsible for the character selection and behaviours

class Player : public GameObject
{
public:
	Player();
	//The below constructor is used for character select if the player has multiple options
	Player(int id);
	~Player() {}

	void PlaceBomb(int bombType);

private:
	
};