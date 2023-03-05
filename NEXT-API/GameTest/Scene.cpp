#include "stdafx.h"
#include "Scene.h"
#include "Map.h"

Scene::Scene():Scene(INTRO){}

Scene::Scene(SCENE_LEVEL_TYPE id):Scene_Type(id)
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
}
