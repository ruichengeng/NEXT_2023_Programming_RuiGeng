#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb() : Bomb(0)
{
}

Bomb::Bomb(int id) : GameObject()
{
	CreateGOSprite(".\\Art\\bomb.bmp", 6, 1, 500.0f, 500.0f, 1.5f);
	CreateGOAnimation(ANIM_BOMB, 1.0f / 25.0f, { 0,1,2,3,4,5 });
}

void Bomb::SetBomb(float xPos, float yPos)
{
	GetSprite()->SetPosition(xPos, yPos);
	isActive = true;
}

void Bomb::UpdateBombState(float deltaTime)
{
	if (triggerTimer > 0.0f)
	{
		triggerTimer -= deltaTime;
	}
	else
	{
		triggerTimer = 0.0f;
		Explode();
	}
	Update(deltaTime);
}

void Bomb::Explode()
{
	isActive = false;
	triggerTimer = 5.0f;
}