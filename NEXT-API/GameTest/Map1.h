#pragma once
#include "MapBase.h"

class Map1 :public MapBase
{
public:
	Map1();
	~Map1() {}

	void CreateEnemyPool(int count, std::vector<Vector2*> gridPaths) override;
	void CreateWallBlockPool(int count) override;
	void CreateGrid(int x, int y) override;

	void CreateChildrenElements();
};