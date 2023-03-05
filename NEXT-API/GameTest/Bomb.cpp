#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb() : Bomb(0)
{
}

Bomb::Bomb(int id) : GameObject()
{
	CreateGOSprite(".\\Art\\bomb2.bmp", 11, 1, 500.0f, 500.0f, 1.0f);
	CreateGOAnimation(ANIM_BOMB, 1.0f / 25.0f, { 0,1,2,3,4,5, 6, 7 });
	CreateGOAnimation(ANIM_BOMB_EXPLOSION, 1.0f / 25.0f, {8, 9, 10});
	
	GetSprite()->SetAnimation(ANIM_BOMB);
}

void Bomb::SetBomb(float xPos, float yPos)
{
	GetSprite()->SetPosition(xPos, yPos);
	isActive = true;
}

void Bomb::UpdateBombState(float deltaTime)
{
	if (isActive)
	{
		if (triggerTimer > 0.0f)
		{
			triggerTimer -= deltaTime * 0.001f;
		}
		else
		{
			if (!Exploded)
			{
				triggerTimer = 0.0f;
				Explode();
			}
			else
			{
				isActive = false;
				Exploded = false;
				GetSprite()->SetAnimation(ANIM_BOMB);
			}
		}
		Update(deltaTime);
	}
}

void Bomb::Explode()
{
	Exploded = true;
	GetSprite()->SetAnimation(ANIM_BOMB_EXPLOSION);
	//isActive = false;
	triggerTimer = 3.0f;
}