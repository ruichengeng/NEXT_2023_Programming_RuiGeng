#pragma once
#include "GameObject.h"

class WallBlock : public GameObject
{
public:
	WallBlock();
	//For different wall types
	// ID: 0 -- Unbreakable wall; 1 -- Breakable wall; 2 -- Breakable wall with loots
	WallBlock(Vector2 pos, Vector2 maxVec, int id = 0);
	~WallBlock() {}

	void CreateWall(Vector2 pos);
	void DestroyWall();

	bool isBreakable = false;
	//Vector2 BlockIndex;
	WallBlockType BlockType;
};