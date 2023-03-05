#pragma once
#include "Enemies.h"
#include "WallBlock.h"

class MapBase
{
public:
	MapBase(SCENE_LEVEL_TYPE type) : Map_Type(type) {}
	~MapBase() {}

	virtual void Update(float deltaTime);
	virtual void Render();

	//For Object Pooling
	//Enemies
	virtual void CreateEnemyPool(int count, std::vector<Vector2*> gridPaths) {}
	//void ReturnEnemy(Enemies* enemy);

	//Getter for the map's enemies
	std::vector<Enemies*> GetMapEnemies();

	//Wall Blocks
	virtual void CreateWallBlockPool(int count) {}
	//void returnWallBlock(WallBlock* wall);

	//Getter for the map's walls
	std::vector<WallBlock*> GetMapWalls();

	//Grid System
	virtual void CreateGrid(int x, int y) {}

	//Reset for replay
	void ResetMap();

public:
	SCENE_LEVEL_TYPE Map_Type = INTRO;

	//Background
	CSimpleSprite* mapBackgroundSprite;

	std::vector<Enemies*> mapEnemyPool;
	std::vector<WallBlock*> mapWallBlocks;

	//Grid
	std::vector<Vector2> mapGridIntersections;
};