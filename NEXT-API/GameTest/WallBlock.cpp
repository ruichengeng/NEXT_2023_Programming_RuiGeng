#include "stdafx.h"
#include "WallBlock.h"

WallBlock::WallBlock() : WallBlock(Vector2(0, 0), Vector2(1, 1), 0) {}

WallBlock::WallBlock(Vector2 pos, Vector2 maxVec, int id) : GameObject()
{
	//BlockIndex = posVec;
	BlockType = (WallBlockType)id;

	//Calculate the grid separation
	//float dx = APP_VIRTUAL_WIDTH / maxVec.x;
	//float dy = APP_VIRTUAL_HEIGHT / maxVec.y;

	CreateWall(pos);
}

void WallBlock::CreateWall(Vector2 pos)
{
	//Get the world position
	//float xPos = separation.x * BlockIndex.x;
	//float yPos = separation.y * BlockIndex.y;

	switch (BlockType)
	{
	case INDESTRUCTIBLE:
		CreateGOSprite(".\\Art\\wall_unbreakable.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	case DESTRUCTIBLE:
		CreateGOSprite(".\\Art\\wall_breakable.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	case DESTRUCTIBLE_LOOT:
		CreateGOSprite(".\\Art\\crate_loot.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	case TELEPORT:
		CreateGOSprite(".\\Art\\teleport_effect.bmp", 18, 1, pos.x, pos.y, 1.0f);
		CreateGOAnimation(ANIM_TELEPORT, 1.0f / 10.0f, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17});
		GetSprite()->SetAnimation(ANIM_TELEPORT);
		break;
	default:
		return; //Don't create a wall if it's an unknown type
	}
}

void WallBlock::DestroyWall()
{
}
