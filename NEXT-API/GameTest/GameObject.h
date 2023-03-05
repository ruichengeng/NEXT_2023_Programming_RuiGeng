#pragma once
#include <iostream>
#include <string>
#include "CollisionManager.h"
#include "../GameTest/App/SimpleSprite.h"
#include "app\app.h"
#include "EnumAndHelper.h"

//Game Object Class: this is the base class used for our object oriented program

class GameObject
{
public:
	GameObject(float collisionRadius = 32.0f) : ObjectRadius(collisionRadius) {}
	~GameObject() {}

	void CreateGOSprite(const char* path, int col, int row, float xPos, float yPos, float scale);
	void CreateGOAnimation(unsigned int state, float speed, const std::vector<int>& frames);
	void Move(MovementDirection d);
	void Render();
	void Update(float deltaTime);

	void DrawColliderCircle();
	
	CSimpleSprite* GetSprite();

	bool isActive = true;
	const float ObjectRadius;

private:
	//Animations
	void SetAnimationState(unsigned int state);

	//Variables
	CSimpleSprite* GOSprite;
	Vector2 SpriteHalfSize; //For collision checks
};