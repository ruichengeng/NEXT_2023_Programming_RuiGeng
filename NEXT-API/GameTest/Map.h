#pragma once
#include "Enemies.h"
#include "WallBlock.h"

class Map
{
public:
	Map();
	//Expandable to host multiple map levels
	Map(int id);
	~Map() {}

	void Update(float deltaTime);
	void Render();

	//For Object Pooling
	//Enemies
	void CreateEnemyPool(int count);
	void ReturnEnemy(Enemies* enemy);

	//Wall Blocks
	void CreateWallBlockPool(int count);
	//void returnWallBlock(WallBlock* wall);

private:
	//Background
	CSimpleSprite* mapBackgroundSprite;

	std::vector<Enemies*> mapEnemyPool;
	//std::vector<WallBlock*> mapWallBlocks;
};