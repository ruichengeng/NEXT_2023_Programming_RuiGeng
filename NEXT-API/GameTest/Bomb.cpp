#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb() : Bomb(0, std::vector<Vector2*>())
{
}

Bomb::Bomb(int id, std::vector<Vector2*> emptyPos) : GameObject(), spawnablePos(emptyPos), bombArms(std::vector<BombArm*>())
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

		if (Exploded)
		{
			for (auto arm : bombArms)
			{
				arm->Update(deltaTime);
			}
		}

		Update(deltaTime);
	}
}

void Bomb::Explode()
{
	Exploded = true;
	createBombArms(4, 4); //two blocks on each side
	GetSprite()->SetAnimation(ANIM_BOMB_EXPLOSION);
	//isActive = false;
	triggerTimer = 3.0f;
}

void Bomb::RenderBomb()
{
	Render();
	for (auto arm : bombArms)
	{
		if (Exploded)
		{
			arm->Render();
		}
	}
}

void Bomb::createBombArms(int x, int y)
{
	//Find half width and height
	int hX = x/2;
	int hY = y/2;

	std::vector<Vector2> availableCenterSpots = findAvailablePosObj(this);
	std::vector<Vector2> tempPos = availableCenterSpots;
	std::vector<Vector2> tempPos2 = tempPos;

	//Horizontal - Left
	for (int i = 0; i < hX; i++)
	{
		if (tempPos[2].x != -1 && tempPos[2].y != -1)
		{
			tempPos2 = findAvailablePos(tempPos[2], ObjectRadius, ObjectRadius);

			if (tempPos2[2].x != -1 && tempPos2[2].y != -1)
			{
				//There is an extra space
				
				//Spawn an explosion arm
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_h.bmp", 1, 1, tempPos[2].x, tempPos[2].y, 1.0f);
				bombArms.push_back(arm);

				//Find the next available position
				tempPos = tempPos2;
			}
			else
			{
				//No more space
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_left.bmp", 1, 1, tempPos[2].x, tempPos[2].y, 1.0f);
				bombArms.push_back(arm);
				//Spawn an arm tip
				i += hX;
			}
		}
	}

	//Horizontal - Right
	tempPos = availableCenterSpots;
	for (int i = 0; i < hX; i++)
	{
		if (tempPos[3].x != -1 && tempPos[3].y != -1)
		{
			tempPos2 = findAvailablePos(tempPos[3], ObjectRadius, ObjectRadius);

			if (tempPos2[3].x != -1 && tempPos2[3].y != -1)
			{
				//There is an extra space

				//Spawn an explosion arm
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_h.bmp", 1, 1, tempPos[3].x, tempPos[3].y, 1.0f);
				bombArms.push_back(arm);

				//Find the next available position
				tempPos = tempPos2;
			}
			else
			{
				//No more space
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_right.bmp", 1, 1, tempPos[3].x, tempPos[3].y, 1.0f);
				bombArms.push_back(arm);
				//Spawn an arm tip
				i += hX;
			}
		}
	}

	//Horizontal - Top
	tempPos = availableCenterSpots;
	for (int i = 0; i < hX; i++)
	{
		if (tempPos[1].x != -1 && tempPos[1].y != -1)
		{
			tempPos2 = findAvailablePos(tempPos[1], ObjectRadius, ObjectRadius);

			if (tempPos2[1].x != -1 && tempPos2[1].y != -1)
			{
				//There is an extra space

				//Spawn an explosion arm
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_v.bmp", 1, 1, tempPos[1].x, tempPos[1].y, 1.0f);
				bombArms.push_back(arm);

				//Find the next available position
				tempPos = tempPos2;
			}
			else
			{
				//No more space
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_top.bmp", 1, 1, tempPos[1].x, tempPos[1].y, 1.0f);
				bombArms.push_back(arm);
				//Spawn an arm tip
				i += hX;
			}
		}
	}

	//Horizontal - Down
	tempPos = availableCenterSpots;
	for (int i = 0; i < hX; i++)
	{
		if (tempPos[0].x != -1 && tempPos[0].y != -1)
		{
			tempPos2 = findAvailablePos(tempPos[0], ObjectRadius, ObjectRadius);

			if (tempPos2[0].x != -1 && tempPos2[0].y != -1)
			{
				//There is an extra space

				//Spawn an explosion arm
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_v.bmp", 1, 1, tempPos[0].x, tempPos[0].y, 1.0f);
				bombArms.push_back(arm);

				//Find the next available position
				tempPos = tempPos2;
			}
			else
			{
				//No more space
				BombArm* arm = new BombArm(this);
				arm->CreateGOSprite(".\\Art\\exp_down.bmp", 1, 1, tempPos[0].x, tempPos[0].y, 1.0f);
				bombArms.push_back(arm);
				//Spawn an arm tip
				i += hX;
			}
		}
	}

	//Vertical
	
}

std::vector<Vector2> Bomb::findAvailablePosObj(GameObject* obj)
{
	std::vector<Vector2> availablePos = std::vector<Vector2>();

	float xAi, yAi, radius;
	obj->GetSprite()->GetPosition(xAi, yAi);
	radius = obj->ObjectRadius;

	availablePos.clear();

	for (int i = 0; i < 4; i++)
	{
		availablePos.push_back(Vector2(-1, -1));
	}

	//Expected Values
	//Top
	Vector2 Top = Vector2(xAi, yAi + 2.0f * radius);

	//Down
	Vector2 Down = Vector2(xAi, yAi - 2.0f * radius);

	//Left
	Vector2 Left = Vector2(xAi - 2.0f * radius, yAi);

	//Right
	Vector2 Right = Vector2(xAi + 2.0f * radius, yAi);

	for (auto position : spawnablePos)
	{
		float dX = abs(xAi - position->x);
		float dY = abs(yAi - position->y);

		if ((abs(Top.x - position->x) < radius) && (abs(Top.y - position->y) < radius))
		{
			availablePos[0] = *position;
		}

		if ((abs(Down.x - position->x) < radius) && (abs(Down.y - position->y) < radius))
		{
			availablePos[1] = *position;
		}

		if ((abs(Left.x - position->x) < radius) && (abs(Left.y - position->y) < radius))
		{
			availablePos[2] = *position;
		}

		if ((abs(Right.x - position->x) < radius) && (abs(Right.y - position->y) < radius))
		{
			availablePos[3] = *position;
		}
	}

	return availablePos;
}

std::vector<Vector2> Bomb::findAvailablePos(Vector2 vec, float w, float h)
{
	std::vector<Vector2> availablePos = std::vector<Vector2>();

	float xAi = vec.x;
	float yAi = vec.y;
	float radius = (w + h) / 2.0f;

	availablePos.clear();

	for (int i = 0; i < 4; i++)
	{
		availablePos.push_back(Vector2(-1, -1));
	}

	//Expected Values
	//Top
	Vector2 Top = Vector2(xAi, yAi + 2.0f * radius);

	//Down
	Vector2 Down = Vector2(xAi, yAi - 2.0f * radius);

	//Left
	Vector2 Left = Vector2(xAi - 2.0f * radius, yAi);

	//Right
	Vector2 Right = Vector2(xAi + 2.0f * radius, yAi);

	for (auto position : spawnablePos)
	{
		float dX = abs(xAi - position->x);
		float dY = abs(yAi - position->y);

		if ((abs(Top.x - position->x) < radius) && (abs(Top.y - position->y) < radius))
		{
			availablePos[0] = *position;
		}

		if ((abs(Down.x - position->x) < radius) && (abs(Down.y - position->y) < radius))
		{
			availablePos[1] = *position;
		}

		if ((abs(Left.x - position->x) < radius) && (abs(Left.y - position->y) < radius))
		{
			availablePos[2] = *position;
		}

		if ((abs(Right.x - position->x) < radius) && (abs(Right.y - position->y) < radius))
		{
			availablePos[3] = *position;
		}
	}

	return availablePos;
}
