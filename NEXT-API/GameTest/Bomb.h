#pragma once
#include "GameObject.h"

//Class for the bombs
class Bomb : public GameObject
{
public:
	//Class for a bomb's arms components
	class BombArm : public GameObject
	{
	public:
		BombArm(Bomb* b) : OwnerBomb(b) {}
		~BombArm() {}

		Bomb* OwnerBomb;
	};

public:
	Bomb();
	//For different types of bombs
	Bomb(int id, std::vector<Vector2*> emptyPos);
	~Bomb() {}

	void SetBomb(float xPos, float yPos);
	void UpdateBombState(float deltaTime);
	void RenderBomb();
	void Explode();

	bool Exploded = false;

private:
	//Need both x and y to be even for a uniform star explosion shape
	void createBombArms(int x, int y);
	std::vector<Vector2> findAvailablePosObj(GameObject* obj);
	std::vector<Vector2> findAvailablePos(Vector2 vec, float w, float h);

private:
	float triggerTimer = 5.0f;
	std::vector<BombArm*> bombArms;
	std::vector<Vector2*> spawnablePos;
};