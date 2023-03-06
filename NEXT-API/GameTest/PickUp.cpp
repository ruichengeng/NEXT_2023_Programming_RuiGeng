#include "stdafx.h"
#include "PickUp.h"

PickUp::PickUp(PICKUP_ITEM_TYPES type, Vector2 pos) : PickUp_Type(type)
{
	switch (type)
	{
	case PICKUP_APPLE:
		CreateGOSprite(".\\Art\\pickup_apple.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	case PICKUP_CHERRY:
		CreateGOSprite(".\\Art\\pickup_cherry.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	case PICKUP_KEY:
		CreateGOSprite(".\\Art\\pickup_key.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	case PICKUP_PEAR:
		CreateGOSprite(".\\Art\\pickup_pear.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	case PICKUP_STRAWBERRY:
		CreateGOSprite(".\\Art\\pickup_strawberry.bmp", 1, 1, pos.x, pos.y, 1.0f);
		break;
	default:
		break;
	}
}