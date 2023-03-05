#include "stdafx.h"
#include "MapBase.h"

void MapBase::Update(float deltaTime)
{
	mapBackgroundSprite->Update(deltaTime);

	for (int i = 0; i < mapEnemyPool.size(); i++)
	{
		mapEnemyPool[i]->UpdateEnemy(deltaTime);
	}

	for (auto wall : mapWallBlocks)
	{
		if (wall->BlockType != INDESTRUCTIBLE) wall->Update(deltaTime);
	}
}

void MapBase::Render()
{
	mapBackgroundSprite->Draw();

	//Draws grid lines
	for (int a = 0; a < mapGridIntersections.size() - 1; a++)
	{
		App::DrawLine(mapGridIntersections[a].x, 0.0f, mapGridIntersections[a].x, APP_VIRTUAL_HEIGHT, 0.0f, 0.0f, 0.0f);
		App::DrawLine(0.0f, mapGridIntersections[a].y, APP_VIRTUAL_WIDTH, mapGridIntersections[a].y, 0.0f, 0.0f, 0.0f);
		//App::DrawLine(mapGridIntersections[a].x, mapGridIntersections[a].y, mapGridIntersections[a + 1].x, mapGridIntersections[a + 1].y, 0.0f, 0.0f, 0.0f);
	}

	//Draw Walls and Blocks
	for (int b = 0; b < mapWallBlocks.size(); b++)
	{
		if (mapWallBlocks[b]->isActive) mapWallBlocks[b]->Render();
	}

	//Draw enemies
	for (int e = 0; e < mapEnemyPool.size(); e++)
	{
		if (mapEnemyPool[e]->isActive) mapEnemyPool[e]->Render();
	}
}

std::vector<Enemies*> MapBase::GetMapEnemies()
{
	return mapEnemyPool;
}


std::vector<WallBlock*> MapBase::GetMapWalls()
{
	return mapWallBlocks;
}

void MapBase::ResetMap()
{
	for (auto block : mapWallBlocks)
	{
		block->ResetGameObject();
	}

	for (auto enemy : mapEnemyPool)
	{
		enemy->ResetGameObject();
	}
}