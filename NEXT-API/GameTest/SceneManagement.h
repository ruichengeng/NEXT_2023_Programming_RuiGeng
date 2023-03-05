#pragma once
#include "Map1.h"
#include "SmallMap.h"
#include "Player.h"
#include "Scene.h"


//SceneManagement takes care of the levels and maps within them
//Functions like the game's "core"
class SceneManagement
{
public:
	SceneManagement();
	~SceneManagement() {}

	//Scenes
	void LoadLevel(SCENE_LEVEL_TYPE id, std::vector<std::string>* msgs);

	void UpdateSceneComponents(float deltaTime);
	void UpdateInput(float deltaTime);
	void Render();

private:
	void CollisionChecks();

private:
	Player* player;
	std::vector<Scene*> loadedScenes;//Game Scenes (initial, pause, end)
	std::vector<MapBase*> loadedMaps;//Game Map Levels

	Vector2 activeLevel = Vector2(-1, -1);
	SCENE_LEVEL_TYPE activeType;

	//int gameProgress = -1;

	//Input Delays
	float inputDelay = 0.25f;
	float currentDelay = 0.0f;

	bool isDebug = false;
};