//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Map.h"
#include "Player.h"

//------------------------------------------------------------------------
// Game Variables
//------------------------------------------------------------------------
Map* gameMap;
Player* player;


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....

	//testSprite2 = App::CreateSprite(".\\Art\\bomb.bmp", 6, 1);
	//testSprite2->SetPosition(600.0f, 600.0f);
	//float speed2 = 1.0f / 15.0f;
	//testSprite2->CreateAnimation(ANIM_EXPLOSION, speed2, { 0,1,2,3,4,5});
	//testSprite2->SetScale(1.5f);
	//testSprite2->SetAnimation(ANIM_EXPLOSION);
	//------------------------------------------------------------------------
	player = new Player();
	gameMap = new Map();
}

void CollisionChecks()
{
	//Check between player and impassable walls
	for (auto wall : gameMap->GetMapWalls())
	{
		if (CollisionManager::instance().hasHitAABB(player, wall))
		{
			player->PlayerTouchedWall(wall);
		}
	}

	//Check between player and enemies
	for (auto enemy : gameMap->GetMapEnemies())
	{
		if (CollisionManager::instance().hasHitAABB(player, enemy))
		{
			player->PlayerDied();
		}
	}

	//Check between enemies and walls
	for (auto enemy : gameMap->GetMapEnemies())
	{
		for (auto wall : gameMap->GetMapWalls())
		{
			if (CollisionManager::instance().hasHitAABB(enemy, wall))
			{
				enemy->EnemyTouchedWall(wall);
			}
		}
	}

	//Check between enemies and enemies
	//for (int e1 = 0; e1 < gameMap->GetMapEnemies().size(); e1++)
	//{
	//	for (int e2 = e1 + 1; e2 < gameMap->GetMapEnemies().size(); e2++)
	//	{
	//		if (CollisionManager::instance().hasHitAABB(gameMap->GetMapEnemies()[e1], gameMap->GetMapEnemies()[e2]))
	//		{
	//
	//		}
	//	}
	//}

	////Check between player and impassable walls
	//for (auto wall : gameMap->GetMapWalls())
	//{
	//	if (CollisionManager::instance().hasHit(player, wall))
	//	{
	//		player->PlayerTouchedWall(wall);
	//	}
	//}
	//
	////Check between player and enemies
	//for (auto enemy : gameMap->GetMapEnemies())
	//{
	//	if (CollisionManager::instance().hasHit(player, enemy))
	//	{
	//		player->PlayerDied();
	//	}
	//}

	//Check between enemies and bomb explosions
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	CollisionChecks();

	if ((App::GetController().GetLeftThumbStickX() != 0.0f) || (App::GetController().GetLeftThumbStickY() != 0.0f))
	{
		if (App::GetController().GetLeftThumbStickX() > 0.5f)
		{
			player->Move(MOVE_RIGHT);
		}
		else if (App::GetController().GetLeftThumbStickX() < -0.5f)
		{
			player->Move(MOVE_LEFT);
		}
		
		if (App::GetController().GetLeftThumbStickY() > 0.5f)
		{
			player->Move(MOVE_TOP);
		}
		else if (App::GetController().GetLeftThumbStickY() < -0.5f)
		{
			player->Move(MOVE_DOWN);
		}
	}
	else
	{
		player->Move(MOVE_NONE);
	}

	//if (App::GetController().CheckButton(SPACEBUTTON))

	player->UpdatePlayerElements(deltaTime);
	gameMap->Update(deltaTime);

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		//testSprite->SetScale(testSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		//testSprite->SetScale(testSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		//testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		//testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		//testSprite->SetAnimation(-1);
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::IsKeyPressed(VK_SPACE))
	{
		player->PlaceBomb(0);
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	//------------------------------------------------------------------------
	gameMap->Render();
	player->RenderPlayerElements();

	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	//App::Print(100, 100, "Sample Text");

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	//static float a = 0.0f;
	//float r = 1.0f;
	//float g = 1.0f;
	//float b = 1.0f;
	//a += 0.1f;
	//for (int i = 0; i < 20; i++)
	//{
	//
	//	float sx = 200 + sinf(a + i * 0.1f)*60.0f;
	//	float sy = 200 + cosf(a + i * 0.1f)*60.0f;
	//	float ex = 700 - sinf(a + i * 0.1f)*60.0f;
	//	float ey = 700 - cosf(a + i * 0.1f)*60.0f;
	//	g = (float)i / 20.0f;
	//	b = (float)i / 20.0f;
	//	App::DrawLine(sx, sy, ex, ey,r,g,b);
	//}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	delete player;
	delete gameMap;
}