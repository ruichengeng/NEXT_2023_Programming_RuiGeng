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

	for (auto pickup : mapPickUpItems)
	{
		pickup->Update(deltaTime);
	}

	//Generalizing all the above to allchildren
	//for (auto c : allChildren)
	//{
	//	c->Update(deltaTime);
	//}
}

void MapBase::Render()
{
	mapBackgroundSprite->Draw();

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

	//Draw pickups
	for (int p = 0; p < mapPickUpItems.size(); p++)
	{
		if (mapPickUpItems[p]->isActive) mapPickUpItems[p]->Render();
	}


	//Generalizing all the above to allChildren
	//for (auto c : allChildren)
	//{
	//	if (c->isActive) c->Render();
	//}

	if (Map_Debug)
	{
		//Draws grid lines
		for (int a = 0; a < mapGridIntersections.size() - 1; a++)
		{
			App::DrawLine(mapGridIntersections[a].x, 0.0f, mapGridIntersections[a].x, APP_VIRTUAL_HEIGHT, 0.0f, 0.0f, 0.0f);
			App::DrawLine(0.0f, mapGridIntersections[a].y, APP_VIRTUAL_WIDTH, mapGridIntersections[a].y, 0.0f, 0.0f, 0.0f);
			//App::DrawLine(mapGridIntersections[a].x, mapGridIntersections[a].y, mapGridIntersections[a + 1].x, mapGridIntersections[a + 1].y, 0.0f, 0.0f, 0.0f);
		}
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

std::vector<PickUp*> MapBase::GetMapPickUpItems()
{
	return mapPickUpItems;
}

void MapBase::DrawDebugElements(bool draw)
{
	Map_Debug = draw;

	for (auto child : allChildren)
	{
		child->isDebug = draw;
	}
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

	for (auto item : mapPickUpItems)
	{
		item->ResetGameObject();
	}

	//Generalized all the above with allChildren
	//for (auto c : allChildren)
	//{
	//	c->ResetGameObject();
	//}
}