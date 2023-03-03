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
}

void Player::PlaceBomb(int bombType)
{

}