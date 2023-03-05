#pragma once
#include "Map.h"
#include "Player.h"


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
	void UpdateInput();
	void Render();

private:
	void CollisionChecks();

private:
	Player* player;
	std::vector<Map*> loadedMaps;

	int activeLevel = -1;
};