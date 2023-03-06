#pragma once
#include "MapBase.h"


class SmallMap : public MapBase
{
public:
	SmallMap();
	~SmallMap() {}

	//No Enemies in this map
	void CreateWallBlockPool(int count) override;
	void CreateGrid(int x, int y) override;

	void CreateChildrenElements();

	
};