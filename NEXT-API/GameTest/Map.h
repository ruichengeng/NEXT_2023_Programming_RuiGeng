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



private:
	//Background
	CSimpleSprite* mapBackgroundSprite;

	std::vector<Enemies*> mapEnemies;
	//std::vector<WallBlock*> mapWallBlocks;
};