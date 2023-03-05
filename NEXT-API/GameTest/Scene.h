#pragma once
#include "EnumAndHelper.h"
#include <iostream>
#include <vector>

class CSimpleSprite;

class Scene
{
public:
	Scene();
	Scene(SCENE_LEVEL_TYPE id, std::vector<std::string>* msgs);
	~Scene() {}

	void SetRenderText(std::string text);
	void Render();
	void SetSceneString(std::vector<std::string>* msgs);

	SCENE_LEVEL_TYPE Scene_Type;

private:
	CSimpleSprite* sceneBackground;
	std::vector<std::string>* sceneStrings;
};