#pragma once
#include "EnumAndHelper.h"
//CollisionManager: this class has collision check and math help functionalities

class GameObject;

//Collision Manager is a singleton
class CollisionManager
{
private:
	CollisionManager() {}
	~CollisionManager() {}

public:
	static CollisionManager& instance()
	{
		static CollisionManager _instance;
		return _instance;
	}

	bool checkIsColliding(GameObject* obj1, GameObject* obj2);

	//Radius Check
	static bool hasHit(GameObject* obj1, GameObject* obj2);
	//AABB Check
	static bool hasHitAABB(GameObject* obj1, GameObject* obj2);
	static bool hasHitAABB(Vector2 vec1, Vector2 vec2, float dx, float dy);
};