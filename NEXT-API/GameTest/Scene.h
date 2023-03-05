#pragma once
#include "EnumAndHelper.h"
#include <iostream>

class CSimpleSprite;

class Scene
{
public:
	Scene();
	Scene(SCENE_LEVEL_TYPE id);
	~Scene() {}

	void SetRenderText(std::string text);
	void Render();

	SCENE_LEVEL_TYPE Scene_Type;

private:
	std::string renderText;
	std::string renderKeyControlInfo;
	CSimpleSprite* sceneBackground;
};