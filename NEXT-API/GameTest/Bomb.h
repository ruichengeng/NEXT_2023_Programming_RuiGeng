#pragma once
#include "GameObject.h"

class Bomb : public GameObject
{
public:
	Bomb();
	//For different types of bombs
	Bomb(int id);
	~Bomb() {}

	void SetBomb(float xPos, float yPos);
	void UpdateBombState(float deltaTime);
	void Explode();

	bool Exploded = false;

private:
	float triggerTimer = 5.0f;
};