#pragma once

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