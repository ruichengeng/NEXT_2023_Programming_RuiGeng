#pragma once
#include <vector>
#include "EnumAndHelper.h"

//AI Class for the behaviour of the enemies, can be expanded to non-hostile enemies

class Vector2;
class GameObject;
class AI
{
public:
	AI() : AI(nullptr) {}
	AI(GameObject* obj);
	~AI() {}

	void SetUpPath(std::vector<Vector2*> path);
	void SetTarget(GameObject* target); //For enemies that seek the player or other targets
	
	//AI Behaviours
	void Patrol(); //For patrols on a fixed path
	void Chase();

	void UpdateAI(float deltaTime);

	AI_TYPES ai_Type;
	MovementDirection patrolDirection;

private:
	void moving();
	void findNextPos();

private:
	GameObject* ai_Character;
	GameObject* obj_OfInterest;
	Vector2* nextPosition;
	std::vector<Vector2*> ai_Paths;
	bool inTransition = false;

	std::vector<Vector2*> availablePos;
};