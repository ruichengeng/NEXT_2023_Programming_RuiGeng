#include "stdafx.h"
#include "SmallMap.h"

SmallMap::SmallMap() : MapBase(MAP_2)
{
	mapBackgroundSprite = App::CreateSprite(".\\Art\\background_dirt.bmp", 1, 1);
	mapBackgroundSprite->SetPosition(512.0f, 512.0f);
	mapBackgroundSprite->SetScale(1.0f);
	//CreateGrid(8, 8);
}

void SmallMap::CreateWallBlockPool(int count)
{
}

void SmallMap::CreateGrid(int x, int y)
{
	mapGridIntersections.clear();
	mapWallBlocks.clear();
	mapPickUpItems.clear();

	//Distance between the adjascent point
	float dx = APP_VIRTUAL_WIDTH / (x * 2.0f);
	float dy = APP_VIRTUAL_HEIGHT / (y * 2.0f);

	//Quarter distance since this map is exactly 1/4th of and centered at the whole screen
	float qx = APP_VIRTUAL_WIDTH / 4.0f;
	float qy = APP_VIRTUAL_HEIGHT / 4.0f;

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

			mapGridIntersections.push_back(Vector2(i * dx + qx, j * dy + qy));

			///
			/// Temporary Values, can be generalized according to a rule and seeds
			///

			//Checks for border points
			if (((i == x) || (i == 0)) || ((j == y) || (j == 0)))
			{
				borderPoints.push_back(new Vector2(i * dx + qx, j * dy + qy));
				gridOccupiedByBlock = true;
			}

			if (i > 1 && j > 1)
			{
				if (i % 2 == 0 && j % 2 == 0)
				{
					evenGridPoints.push_back(new Vector2(i * dx + qx, j * dy + qy));
					gridOccupiedByBlock = true;
				}
			}

			if (i == 3 && j == 7)
			{
				WallBlock* newWallBlock = new WallBlock(Vector2(i * dx + qx, j * dy + qy), Vector2(x, y), 3);
				mapWallBlocks.push_back(newWallBlock);

				gridOccupiedByBlock = true;
			}
			else if (i == 5 && j == 7)
			{
				WallBlock* newWallBlock = new WallBlock(Vector2(i * dx + qx, j * dy + qy), Vector2(x, y), 2);
				mapWallBlocks.push_back(newWallBlock);

				gridOccupiedByBlock = true;
			}
			else if (i == 1 && j == 3)
			{
				WallBlock* newWallBlock = new WallBlock(Vector2(i * dx + qx, j * dy + qy), Vector2(x, y), 2);
				mapWallBlocks.push_back(newWallBlock);

				gridOccupiedByBlock = true;
			}
			else if (i == 1 && j == 1)
			{
				mapPickUpItems.push_back(new PickUp(PICKUP_APPLE, Vector2(i * dx + qx, j * dy + qy)));
				gridOccupiedByBlock = true;
			}
			else if (i == 3 && j == 1)
			{
				mapPickUpItems.push_back(new PickUp(PICKUP_CHERRY, Vector2(i * dx + qx, j * dy + qy)));
				gridOccupiedByBlock = true;
			}
			else if (i == 5 && j == 1)
			{
				mapPickUpItems.push_back(new PickUp(PICKUP_KEY, Vector2(i * dx + qx, j * dy + qy)));
				gridOccupiedByBlock = true;
			}
			else if (i == 7 && j == 5)
			{
				mapPickUpItems.push_back(new PickUp(PICKUP_PEAR, Vector2(i * dx + qx, j * dy + qy)));
				gridOccupiedByBlock = true;
			}
			else if (i == 7 && j == 7)
			{
				mapPickUpItems.push_back(new PickUp(PICKUP_STRAWBERRY, Vector2(i * dx + qx, j * dy + qy)));
				gridOccupiedByBlock = true;
			}

			if (!gridOccupiedByBlock) emptyGridPoints.push_back(new Vector2(i * dx + qx, j * dy + qy));
		}
	}


	//Creates the wall block pool

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
	CreateChildrenElements();
}

void SmallMap::CreateChildrenElements()
{
	allChildren.clear();

	for (auto w : mapWallBlocks)
	{
		allChildren.push_back(w);
	}

	for (auto p : mapPickUpItems)
	{
		allChildren.push_back(p);
	}
}