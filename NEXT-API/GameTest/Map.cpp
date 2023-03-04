#include "stdafx.h"
#include "Map.h"

Map::Map() : Map(0) {}

Map::Map(int id)
{
	mapBackgroundSprite = App::CreateSprite(".\\Art\\blankBackground.bmp", 1, 1);
	mapBackgroundSprite->SetPosition(512.0f, 384.0f);
	CreateEnemyPool(5);
	CreateGrid(20, 20);
}

void Map::Update(float deltaTime)
{
	mapBackgroundSprite->Update(deltaTime);

	for (int i = 0; i < mapEnemyPool.size(); i++)
	{
		mapEnemyPool[i]->Update(deltaTime);
	}

	for (auto wall : mapWallBlocks)
	{
		if (wall->BlockType != INDESTRUCTIBLE) wall->Update(deltaTime);
	}
}

void Map::Render()
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

void Map::CreateEnemyPool(int count)
{
	mapEnemyPool.clear();

	for (int e = 0; e < count; e++)
	{
		mapEnemyPool.push_back(new Enemies());
	}
}

std::vector<Enemies*> Map::getMapEnemies()
{
	return mapEnemyPool;
}

void Map::CreateGrid(int x, int y)
{
	mapGridIntersections.clear();

	//Distance between the adjascent point
	float dx = APP_VIRTUAL_WIDTH / x;
	float dy = APP_VIRTUAL_HEIGHT / y;


	//Creates the intersection points
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			mapGridIntersections.push_back(Vector2(i * dx, j * dy));
		}
	}

	
	//Creates the wall block pool

	//TESTING
	//jkladsfhljkdshfkajsdhfjklahsdfjkhasdklf

	mapWallBlocks.clear();

	for (int b = 0; b < 50; b++)
	{
		//Temp for testing

		WallBlock* newWallBlock = new WallBlock(mapGridIntersections[b], Vector2(x, y), rand()%3);

		//-----------------------------
		mapWallBlocks.push_back(newWallBlock);
	}



	//"Path finding" for AI and player
}
