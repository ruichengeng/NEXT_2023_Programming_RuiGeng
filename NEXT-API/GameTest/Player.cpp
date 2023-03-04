#include "stdafx.h"
#include "Player.h"

Player::Player():Player(0) {}

Player::Player(int id):GameObject()
{
	//For character selection, the id can be added to the end of the name. I.e: Player0, Player1, etc
	CreateGOSprite(".\\Art\\NeoEarlyBomberman.bmp", 7, 4, 400.0f, 400.0f, 1.5f);
	CreateGOAnimation(ANIM_BACKWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6 });
	CreateGOAnimation(ANIM_RIGHT, 1.0f / 15.0f, { 7,8,9,10,11,12,13 });
	CreateGOAnimation(ANIM_FORWARDS, 1.0f / 15.0f, { 14,15,16,17,18,19,20 });
	CreateGOAnimation(ANIM_LEFT, 1.0f / 15.0f, { 21,22,23,24,25,26,27 });

	playerStatistics = PlayerStat();

	bombPool.clear();
	AddToBombPool(10, 0);
}

void Player::PlaceBomb(int bombType)
{
	float x, y;
	GetSprite()->GetPosition(x, y);

	for (int a = 0; a < bombPool.size(); a++)
	{
		if (!bombPool[a]->Exploded && !bombPool[a]->isActive)
		{
			bombPool[a]->SetBomb(x, y);
			return;
		}
	}

	AddToBombPool(1, bombType);
	PlaceBomb(bombType);
}

void Player::AddToBombPool(int count, int bombType)
{
	for (int b = 0; b < count; b++)
	{
		Bomb* newBomb = new Bomb(bombType);
		newBomb->isActive = false;
		bombPool.push_back(newBomb);
	}
}

void Player::UpdatePlayerElements(float deltaTime)
{
	playerStatistics.timeElapsed += deltaTime;
	Update(deltaTime);

	for (int i = 0; i < bombPool.size(); i++)
	{
		if (bombPool[i]->isActive) bombPool[i]->UpdateBombState(deltaTime);
	}
}

void Player::RenderPlayerElements()
{
	Render();

	for (int i = 0; i < bombPool.size(); i++)
	{
		if (bombPool[i]->isActive) bombPool[i]->Render();
	}

	RenderUIComponents();
}

void Player::RenderUIComponents()
{
	std::string lives = "HP: " + std::to_string(playerStatistics.Lives);
	std::string bomb = "Bomb: " + std::to_string(playerStatistics.BombCount);
	std::string time = "Time: " + std::to_string((int)roundf(playerStatistics.timeElapsed)) + "s";
	App::Print(512, 700, lives.c_str(), 0.0f, 0.0f, 0.0f);
	App::Print(512, 600, bomb.c_str(), 0.0f, 0.0f, 0.0f);
	App::Print(512, 500, time.c_str(), 0.0f, 0.0f, 0.0f);
}
