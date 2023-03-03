#pragma once

//CollisionManager: this class has collision check and math help functionalities

//Basic Math Structures
struct Vector2
{
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float xComp, float yComp) : x(xComp), y(yComp) {}

	float x, y;
};

struct Vector3
{
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float xComp, float yComp, float zComp) : x(xComp), y(yComp), z(zComp) {}

	float x, y, z;
};

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
};