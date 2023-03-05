#include "stdafx.h"
#include "AI.h"
#include "GameObject.h"

AI::AI(GameObject* obj) : ai_Character(obj) 
{
	nextPosition = new Vector2();
	obj->GetSprite()->GetPosition(nextPosition->x, nextPosition->y);
}

void AI::SetUpPath(std::vector<Vector2*> path)
{
	ai_Paths = path;
}

void AI::SetTarget(GameObject* target)
{
	obj_OfInterest = target;
}

void AI::Patrol()
{

}

void AI::Chase()
{
}

void AI::UpdateAI(float deltaTime)
{
	inTransition ? moving() : findNextPos();
}

void AI::moving()
{
	float x, y;
	ai_Character->GetSprite()->GetPosition(x, y);

	float dX = nextPosition->x - x;
	float dY = nextPosition->y - y;

	if (sqrtf((dX * dX) + (dY * dY)) < 0.01f)
	{
		inTransition = false;
		return;
	}

	//(dX < dY) ? dX = nextPosition.x : dY = nextPosition.y;

	if (abs(dX) < abs(dY))
	{
		ai_Character->GetSprite()->SetPosition(nextPosition->x, y);
		//Move Vertical
		//dX = nextPosition->x;
		//(dY < 0.0f) ? ai_Character->Move(MOVE_DOWN) : ai_Character->Move(MOVE_TOP);
	}
	else
	{
		ai_Character->GetSprite()->SetPosition(x, nextPosition->y);
		//Move Horizontal
		//dY = nextPosition->y;
		//(dX < 0.0f) ? ai_Character->Move(MOVE_LEFT) : ai_Character->Move(MOVE_RIGHT);
	}
	ai_Character->Move(patrolDirection);
}

void AI::findNextPos()
{
	//Make sure it's at the center of the current nextPosition
	if (nextPosition != nullptr && nextPosition != new Vector2())
	{
		ai_Character->GetSprite()->SetPosition(nextPosition->x, nextPosition->y);
	}

	float xAi, yAi, radius;
	ai_Character->GetSprite()->GetPosition(xAi, yAi);
	radius = ai_Character->ObjectRadius;

	availablePos.clear(); 

	for (int i = 0; i < 4; i++)
	{
		availablePos.push_back(nullptr);
	}
	// 0 - top, 1 - down, 2 - left, 3 - right

	//Expected Values
	//Top
	Vector2 Top = Vector2(xAi, yAi + 2.0f * radius);

	//Down
	Vector2 Down = Vector2(xAi, yAi - 2.0f * radius);

	//Left
	Vector2 Left = Vector2(xAi - 2.0f * radius, yAi);

	//Right
	Vector2 Right = Vector2(xAi + 2.0f * radius, yAi);


	for (auto position : ai_Paths)
	{
		float dX = abs(xAi - position->x);
		float dY = abs(yAi - position->y);

		if ((abs(Top.x - position->x) < radius) && (abs(Top.y - position->y) < radius))
		{
			availablePos[0] = position;
		}

		if ((abs(Down.x - position->x) < radius) && (abs(Down.y - position->y) < radius))
		{
			availablePos[1] = position;
		}

		if ((abs(Left.x - position->x) < radius) && (abs(Left.y - position->y) < radius))
		{
			availablePos[2] = position;
		}
		
		if ((abs(Right.x - position->x) < radius) && (abs(Right.y - position->y) < radius))
		{
			availablePos[3] = position;
		}


		//Temp for debug:
		if (availablePos[0] != nullptr)
		{
			
			std::cout << "Available Top x:" << availablePos[0]->x << " y: " << availablePos[0]->y << std::endl;
		}
		else
		{
			std::cout << "Unavailable Top .................." << std::endl;
		}

		if (availablePos[1] != nullptr)
		{
			std::cout << "Available Down x:" << availablePos[1]->x << " y: " << availablePos[1]->y << std::endl;
		}
		else
		{
			std::cout << "Unavailable Down .................." << std::endl;
		}

		if (availablePos[2] != nullptr)
		{
			std::cout << "Available Left x:" << availablePos[2]->x << " y: " << availablePos[2]->y << std::endl;
		}
		else
		{
			std::cout << "Unavailable Left .................." << std::endl;
		}

		if (availablePos[3] != nullptr)
		{
			std::cout << "Available Right x:" << availablePos[3]->x << " y: " << availablePos[3]->y << std::endl;
		}
		else
		{
			std::cout << "Unavailable Right .................." << std::endl;
		}

		//if (dY <= ai_Character->ObjectRadius*2.0f && dX <= ai_Character->ObjectRadius*2.0f)
		//{
		//	(xAi > position->x) ? availablePos[2] = position : availablePos[3] = position;
		//    (yAi > position->y) ? availablePos[1] = position : availablePos[0] = position;
		//
		//
		//	//(xAi > position.x) ? availablePos[2] = &position : availablePos[3] = &position;
		//	//(yAi > position.y) ? availablePos[1] = &position : availablePos[0] = &position;
		//}
	}

	switch (patrolDirection)
	{
	case MOVE_TOP:
		if (availablePos[0] != nullptr)
		{
			nextPosition = availablePos[0];
		}
		else
		{
			patrolDirection = MOVE_DOWN;
			if (availablePos[1] != nullptr) nextPosition = availablePos[1];
		}
		break;
	case MOVE_DOWN:
		if (availablePos[1] != nullptr)
		{
			nextPosition = availablePos[1];
		}
		else
		{
			patrolDirection = MOVE_TOP;
			if (availablePos[0] != nullptr) nextPosition = availablePos[0];
			//nextPosition = availablePos[0];
		}
		break;
	case MOVE_LEFT:
		if (availablePos[2] != nullptr)
		{
			nextPosition = availablePos[2];
		}
		else
		{
			//nextPosition = availablePos[3];
			patrolDirection = MOVE_RIGHT;
			if (availablePos[3] != nullptr) nextPosition = availablePos[3];
		}
		break;
	case MOVE_RIGHT:
		if (availablePos[3] != nullptr)
		{
			nextPosition = availablePos[3];
		}
		else
		{
			//nextPosition = availablePos[2];
			patrolDirection = MOVE_LEFT;
			if (availablePos[2] != nullptr) nextPosition = availablePos[2];
		}
		break;
	}

	switch (ai_Type)
	{
	case PATROL:

		

		//nextPosition
		break;
	case CHASE:
		break;
	default:
		break;
	}

	inTransition = true;
}