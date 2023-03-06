#include "stdafx.h"
#include "Map1.h"

Map1::Map1():MapBase(MAP_1)
{
	mapBackgroundSprite = App::CreateSprite(".\\Art\\background_grass.bmp", 1, 1);
	mapBackgroundSprite->SetPosition(512.0f, 512.0f);
	mapBackgroundSprite->SetScale(1.0f);

	CreateGrid(16, 16);
}

void Map1::CreateEnemyPool(int count, std::vector<Vector2*> gridPaths)
{
	mapEnemyPool.clear();

	for (int e = 0; e < count; e++)
	{
		//Enemies* newEnemy = new Enemies(rand() % 4, gridPaths); Random Enemy Type Spawn, under testing
		Enemies* newEnemy = new Enemies(e % 4, gridPaths);
		newEnemy->SetEnemyState(Vector2(128.0f + e * 128, 128.0f + e * 128), (MovementDirection)(1 + (e%4)));
		mapEnemyPool.push_back(newEnemy);
	}
}

void Map1::CreateWallBlockPool(int count)
{
}

void Map1::CreateGrid(int x, int y)
{
	mapGridIntersections.clear();
	mapWallBlocks.clear();

	//Distance between the adjascent point
	float dx = APP_VIRTUAL_WIDTH / x;
	float dy = APP_VIRTUAL_HEIGHT / y;


	//Border
	std::vector<Vector2*> borderPoints;
	//Even grid points
	std::vector<Vector2*> evenGridPoints;
	//Empty grid points for the ai behaviours
	emptyGridPoints.clear();

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

			if (i == 11 && j == 5)
			{
				WallBlock* newWallBlock = new WallBlock(Vector2(i * dx, j * dy), Vector2(x, y), 3);
				mapWallBlocks.push_back(newWallBlock);

				gridOccupiedByBlock = true;
			}

			if (!gridOccupiedByBlock) emptyGridPoints.push_back(new Vector2(i * dx, j * dy));
		}
	}


	//Creates the wall block pool

	//TESTING
	//jkladsfhljkdshfkajsdhfjklahsdfjkhasdklf


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
	CreateEnemyPool(5, emptyGridPoints);
	CreateChildrenElements();
}

void Map1::CreateChildrenElements()
{
	allChildren.clear();

	for (auto e : mapEnemyPool)
	{
		allChildren.push_back(e);
	}

	for (auto w : mapWallBlocks)
	{
		allChildren.push_back(w);
	}
}