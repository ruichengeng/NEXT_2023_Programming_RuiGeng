#include "stdafx.h"
#include "GameObject.h"

void GameObject::CreateGOSprite(const char* path, int col, int row, float xPos, float yPos, float scale)
{
	GOSprite = App::CreateSprite(path, col, row);
	GOSprite->SetPosition(xPos, yPos);
	GOSprite->SetScale(scale);
}

void GameObject::CreateGOAnimation(unsigned int state, float speed, const std::vector<int>& frames)
{
	GOSprite->CreateAnimation(state, speed, frames);
}

void GameObject::Move(MovementDirection d)
{
	if (d == MOVE_NONE)
	{
		GOSprite->SetAnimation(-1);
		return;
	}

	float x, y;
	GOSprite->GetPosition(x, y);

	switch (d)
	{
	case MOVE_DOWN:
		GOSprite->SetAnimation(ANIM_BACKWARDS);
		GOSprite->SetPosition(x, y + 2.0f);
		break;
	case MOVE_TOP:
		GOSprite->SetAnimation(ANIM_FORWARDS);
		GOSprite->SetPosition(x, y - 2.0f);
		break;
	case MOVE_LEFT:
		GOSprite->SetAnimation(ANIM_LEFT);
		GOSprite->SetPosition(x - 2.0f, y);
		break;
	case MOVE_RIGHT:
		GOSprite->SetAnimation(ANIM_RIGHT);
		GOSprite->SetPosition(x + 2.0f, y);
		break;
	default:
		break;
	}
}

void GameObject::Render()
{
	if (isActive)
	{
		GOSprite->Draw();
		DrawColliderCircle();
	}
}

void GameObject::Update(float deltaTime)
{
	if(isActive) GOSprite->Update(deltaTime);
}

void GameObject::DrawColliderCircle()
{
	float x, y;
	GOSprite->GetPosition(x, y);

	App::DrawLine(x, y, x + ObjectRadius, y, 0.0f, 1.0f, 0.0f);
	//static float d = 0.0f;
	//d += 0.1f;
	//
	//
	//
	//float x, y;
	//GOSprite->GetPosition(x, y);
	//App::DrawLine(x, y, x, y + 25.0f, 0.0f, 0.0f);
	//
	//for (int i = 0; i < PI * 2.0f; i += PI/0.125f)
	//{
	//	Vector2 pos_Start = Vector2(25.0f * cosf(i) + x, 25.0f * sinf(i) + y);
	//	Vector2 pos_End = Vector2(25.0f * cosf(i + PI / 0.125f) + x, 25.0f * sinf(i + PI / 0.125f) + y);
	//	App::DrawLine(pos_Start.x, pos_Start.y, pos_End.x, pos_End.y, 0.0f, 0.0f, 0.0f);
	//}
}

CSimpleSprite* GameObject::GetSprite()
{
	return GOSprite;
}
