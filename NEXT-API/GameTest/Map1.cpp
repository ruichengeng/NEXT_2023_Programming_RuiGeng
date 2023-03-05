#include "stdafx.h"
#include "Map1.h"

Map1::Map1():MapBase(MAP_1)
{
	mapBackgroundSprite = App::CreateSprite(".\\Art\\blankBackground.bmp", 1, 1);
	mapBackgroundSprite->SetPosition(512.0f, 512.0f);
	mapBackgroundSprite->SetScale(1.0f);

	CreateGrid(16, 16);
}

void Map1::CreateEnemyPool(int count, std::vector<Vector2*> gridPaths)
{
	mapEnemyPool.clear();

	for (int e = 0; e < count; e++)
	{
		mapEnemyPool.push_back(new Enemies(rand() % 4, gridPaths));
	}
}

void Map1::CreateWallBlockPool(int count)
{
}

void Map1::CreateGrid(int x, int y)
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
			if (((i == x) || (i == 0)) || ((j == y) || (j == 0)))
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
}