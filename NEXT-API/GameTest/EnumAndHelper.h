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

enum PLAYER_TYPES
{
	PLAYER_DEFAULT,
	PLAYER_RED,
	PLAYER_BLUE
};

enum PICKUP_ITEM_TYPES
{
	PICKUP_APPLE,
	PICKUP_PEAR,
	PICKUP_STRAWBERRY,
	PICKUP_CHERRY,
	PICKUP_KEY
};

enum ENEMY_TYPE
{
	ENEMY_GREEN,
	ENEMY_BLUE,
	ENEMY_PURPLE,
	ENEMY_SAND,
	ENEMY_PAC
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
	DESTRUCTIBLE_LOOT,
	TELEPORT
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
	ANIM_BOMB_EXPLOSION,

	//For Teleporter/Portal
	ANIM_TELEPORT

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
