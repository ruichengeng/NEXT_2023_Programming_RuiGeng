#pragma once
#include "CollisionManager.h"
#include "../GameTest/App/SimpleSprite.h"
#include "EnumClasses.h"

//Game Object Class: this is the base class used for our object oriented program

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}

	void CreateGOSprite(const char* path, int col, int row, float xPos, float yPos, float scale);
	void CreateGOAnimation(unsigned int state, float speed, const std::vector<int>& frames);
	void Move(MovementDirection d);
	void Render();
	void Update(float deltaTime);

private:
	//Animations
	void SetAnimationState(unsigned int state);

	//Variables
	CSimpleSprite* GOSprite;
};