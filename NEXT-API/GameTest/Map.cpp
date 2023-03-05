#include "stdafx.h"
#include "Map.h"

Map::Map() : Map(INTRO) {}

Map::Map(SCENE_LEVEL_TYPE id) : Map_Type(id)
{
	mapBackgroundSprite = App::CreateSprite(".\\Art\\blankBackground.bmp", 1, 1);
	mapBackgroundSprite->SetPosition(512.0f, 512.0f);
	mapBackgroundSprite->SetScale(1.0f);
	
	CreateGrid(16, 16);
}

void Map::Update(float deltaTime)
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

void Map::CreateEnemyPool(int count, std::vector<Vector2*> gridPaths)
{
	mapEnemyPool.clear();

	for (int e = 0; e < count; e++)
	{
		mapEnemyPool.push_back(new Enemies(rand()%4, gridPaths));
	}
}

std::vector<Enemies*> Map::GetMapEnemies()
{
	return mapEnemyPool;
}

std::vector<WallBlock*> Map::GetMapWalls()
{
	return mapWallBlocks;
}

void Map::CreateGrid(int x, int y)
{
	mapGridIntersections.clear();

	//Distance between the adjascent point
	float dx = APP_VIRTUAL_WIDTH / x;
	float dy = APP_VIRTUAL_HEIGHT / y;


	//Border
	std::vector<Vector2*> borderPoints;
	//Even grid points
	std::vector<Vector2*> evenGridPoints;
	//Empty grid points for the ai behaviours
	std::vector<Vector2*> emptyGridPoints;

	//Creates the intersection points
	for (int i = 0; i <= x; i++)
	{
		for (int j = 0; j <= y; j++)
		{
			bool gridOccupiedByBlock = false;

			mapGridIntersections.push_back(Vector2(i * dx, j * dy));

			//Checks for border points
			if (((i == x)||(i == 0)) || ((j == y) ||(j == 0)))
			{
				borderPoints.push_back(new Vector2(i * dx, j * dy));
				gridOccupiedByBlock = true;
			}

			if (i > 1 && j > 1)
			{
				if (i % 2 == 0 && j % 2 == 0)
				{
					evenGridPoints.push_back(new Vector2(i * dx, j * dy));
					gridOccupiedByBlock = true;
				}
			}

			if (!gridOccupiedByBlock) emptyGridPoints.push_back(new Vector2(i * dx, j * dy));
		}
	}

	
	//Creates the wall block pool

	//TESTING
	//jkladsfhljkdshfkajsdhfjklahsdfjkhasdklf

	mapWallBlocks.clear();

	for (auto border : borderPoints)
	{
		WallBlock* newWallBlock = new WallBlock(*border, Vector2(x, y), 0);
		mapWallBlocks.push_back(newWallBlock);
	}

	for (auto eP : evenGridPoints)
	{
		WallBlock* newWallBlock = new WallBlock(*eP, Vector2(x, y), 0);
		mapWallBlocks.push_back(newWallBlock);
	}


	//Empty Grid Points
	CreateEnemyPool(1, emptyGridPoints);



	//for (auto emptyGrid : emptyGridPoints)
	//{
	//	WallBlock* newWallBlock = new WallBlock(emptyGrid, Vector2(x, y), 1);
	//	mapWallBlocks.push_back(newWallBlock);
	//}
	
	//Finding the border first

	//for (auto border : mapGridIntersections)
	//{
	//	if (((border.x == 0.0f) || (border.x == APP_VIRTUAL_WIDTH)) || ((border.y == 0.0f) || (border.y == APP_VIRTUAL_HEIGHT)))
	//	{
	//		WallBlock* newWallBlock = new WallBlock(border, Vector2(x, y), 0);
	//		mapWallBlocks.push_back(newWallBlock);
	//	}
	//}
	//

	//for (int b = 0; b < 50; b++)
	//{
	//	//Temp for testing
	//
	//	WallBlock* newWallBlock = new WallBlock(mapGridIntersections[b], Vector2(x, y), rand()%3);
	//
	//	//-----------------------------
	//	mapWallBlocks.push_back(newWallBlock);
	//}



	//"Path finding" for AI and player


}
