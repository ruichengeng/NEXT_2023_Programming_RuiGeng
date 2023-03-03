#include "stdafx.h"
#include "app\app.h"
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
		GOSprite->SetPosition(x, y + 1.0f);
		break;
	case MOVE_TOP:
		GOSprite->SetAnimation(ANIM_FORWARDS);
		GOSprite->SetPosition(x, y - 1.0f);
		break;
	case MOVE_LEFT:
		GOSprite->SetAnimation(ANIM_LEFT);
		GOSprite->SetPosition(x - 1.0f, y);
		break;
	case MOVE_RIGHT:
		GOSprite->SetAnimation(ANIM_RIGHT);
		GOSprite->SetPosition(x + 1.0f, y);
		break;
	default:
		break;
	}
}

void GameObject::Render()
{
	GOSprite->Draw();
}

void GameObject::Update(float deltaTime)
{
	GOSprite->Update(deltaTime);
}
