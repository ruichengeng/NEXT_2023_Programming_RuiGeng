#include "stdafx.h"
#include "Map.h"

Map::Map() : Map(0) {}

Map::Map(int id)
{
	for (int e = 0; e < 1; e++)
	{
		mapEnemies.push_back(new Enemies());
	}
}

void Map::Update(float deltaTime)
{
	for (int i = 0; i < mapEnemies.size(); i++)
	{
		mapEnemies[i]->Update(deltaTime);
	}
}

void Map::Render()
{
	for (int i = 0; i < mapEnemies.size(); i++)
	{
		mapEnemies[i]->Render();
	}
}
