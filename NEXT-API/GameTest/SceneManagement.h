#pragma once
#include "Map.h"
#include "Player.h"


//SceneManagement takes care of the scenes and maps within them
class SceneManagement
{
public:
	SceneManagement();
	~SceneManagement() {}

	//Scenes
	void LoadScene(int id);

	void LoadMap(int id);
	void UpdateSceneComponents(float deltaTime);

private:
	Player* player;
	std::vector<Map*> loadedMaps;
};