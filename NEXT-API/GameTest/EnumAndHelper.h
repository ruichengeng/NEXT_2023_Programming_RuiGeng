#pragma once

//All Enum Types Used

enum SCENE_LEVEL_TYPE
{
	INTRO,
	PAUSE,
	MAP_1,
	MAP_2,
	END
};

enum AI_TYPES
{
	PATROL,
	CHASE
};

enum WallBlockType
{
	INDESTRUCTIBLE,
	DESTRUCTIBLE,
	DESTRUCTIBLE_LOOT
};

enum AnimationType
{
	//Movement player+enemies ---- expandable for more features like hurt, dizziness, effects of spells, etc
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,

	//For Explosion
	ANIM_BOMB,
	ANIM_BOMB_EXPLOSION

	//For Enemies
};

//Enum for game object's movement direction
enum MovementDirection
{
	MOVE_NONE,
	MOVE_TOP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};


//Helpers

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
