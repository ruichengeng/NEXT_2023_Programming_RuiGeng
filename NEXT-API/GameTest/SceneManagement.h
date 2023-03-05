#pragma once
#include "Map.h"
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
	void LoadLevel(SCENE_LEVEL_TYPE id);

	void UpdateSceneComponents(float deltaTime);
	void UpdateInput(float deltaTime);
	void Render();

private:
	void CollisionChecks();

private:
	Player* player;
	std::vector<Scene*> loadedScenes;//Game Scenes (initial, pause, end)
	std::vector<Map*> loadedMaps;//Game Map Levels

	Vector2 activeLevel = Vector2(-1, -1);
	SCENE_LEVEL_TYPE activeType;

	//Input Delays
	float inputDelay = 0.5f;
	float currentDelay = 0.0f;
};