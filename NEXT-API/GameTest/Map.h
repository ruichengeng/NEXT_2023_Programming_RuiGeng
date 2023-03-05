#pragma once
#include "Enemies.h"
#include "WallBlock.h"

class Map
{
public:
	Map();
	//Expandable to host multiple map levels
	Map(SCENE_LEVEL_TYPE id);
	~Map() {}

	void Update(float deltaTime);
	void Render();

	//For Object Pooling
	//Enemies
	void CreateEnemyPool(int count, std::vector<Vector2*> gridPaths);
	//void ReturnEnemy(Enemies* enemy);

	//Getter for the map's enemies
	std::vector<Enemies*> GetMapEnemies();

	//Wall Blocks
	void CreateWallBlockPool(int count);
	//void returnWallBlock(WallBlock* wall);

	//Getter for the map's walls
	std::vector<WallBlock*> GetMapWalls();

	//Grid System
	void CreateGrid(int x, int y);

	SCENE_LEVEL_TYPE Map_Type = MAP_1;

private:
	//Background
	CSimpleSprite* mapBackgroundSprite;

	std::vector<Enemies*> mapEnemyPool;
	std::vector<WallBlock*> mapWallBlocks;

	//Grid
	std::vector<Vector2> mapGridIntersections;
};