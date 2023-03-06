#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
	PickUp(PICKUP_ITEM_TYPES type, Vector2 pos);
	~PickUp() {}

	PICKUP_ITEM_TYPES PickUp_Type;
};