#include "stdafx.h"
#include "Scene.h"
#include "MapBase.h"

Scene::Scene():Scene(INTRO, new std::vector<std::string>()){}

Scene::Scene(SCENE_LEVEL_TYPE id, std::vector<std::string>* msgs):Scene_Type(id), sceneStrings(msgs)
{
	switch (id)
	{
	case INTRO:
		sceneBackground = App::CreateSprite(".\\Art\\intro_title.bmp", 1, 1);
		break;
	case PAUSE:
		sceneBackground = App::CreateSprite(".\\Art\\paused_title.bmp", 1, 1);
		break;
	case END:
		sceneBackground = App::CreateSprite(".\\Art\\end_title.bmp", 1, 1);
		break;
	}

	sceneBackground->SetPosition(512.0f, 712.0f);
}

void Scene::SetRenderText(std::string text)
{
}

void Scene::Render()
{
	sceneBackground->Draw();

	float startPos = 500.0f;

	for (std::string text : *sceneStrings)
	{
		App::Print(400, startPos, text.c_str());
		startPos -= 50.0f;
	}

	//if (Scene_Type == END)
	//{
	//	for (auto text : *sceneStrings)
	//	{
	//		App::Print(512, startPos, text.c_str());
	//		startPos -= 50.0f;
	//	}
	//}

	switch (Scene_Type)
	{
	case INTRO:
		App::Print(400, 500, "'Space' - Start Game - Drop Bomb");
		App::Print(400, 450, "'W, A, S, D' - Movement");
		App::Print(400, 400, "'Left Shift' - Pause Game");
		App::Print(400, 350, "'Right Shift' - Show Collider Debug");
		App::Print(400, 300, "'Esc' - Quit");
		break;
	case PAUSE:
		App::Print(400, 500, "'Left Shift' - Resume");
		App::Print(400, 450, "'Esc' - Quit");
		break;
	case END:
		App::Print(400, 400, "'Left Shift' - Main Menu");
		App::Print(400, 350, "'Esc' - Quit");
		break;
	}
}

void Scene::SetSceneString(std::vector<std::string>* msgs)
{
	sceneStrings = msgs;
}
