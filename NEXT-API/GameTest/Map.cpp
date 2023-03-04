#include "stdafx.h"
#include "Map.h"

Map::Map() : Map(0) {}

Map::Map(int id)
{
	mapBackgroundSprite = App::CreateSprite(".\\Art\\blankBackground.bmp", 1, 1);
	mapBackgroundSprite->SetPosition(512.0f, 384.0f);
	CreateEnemyPool(5);
}

void Map::Update(float deltaTime)
{
	mapBackgroundSprite->Update(deltaTime);

	for (int i = 0; i < mapEnemyPool.size(); i++)
	{
		mapEnemyPool[i]->Update(deltaTime);
	}
}

void Map::Render()
{
	mapBackgroundSprite->Draw();

	for (int i = 0; i < mapEnemyPool.size(); i++)
	{
		if (mapEnemyPool[i]->isActive) mapEnemyPool[i]->Render();
	}
}

void Map::CreateEnemyPool(int count)
{
	mapEnemyPool.clear();

	for (int e = 0; e < count; e++)
	{
		mapEnemyPool.push_back(new Enemies());
	}
}
