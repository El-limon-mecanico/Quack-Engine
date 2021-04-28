#pragma once
#include <queue>

#include "Scene.h"

class SceneMng
{
private:
	std::queue<Scene*> sceneQueue_;

public:
	SceneMng();
	~SceneMng();

	void loadScene(std::string file, std::string sceneName);

	void preUpdate();
	void update();
	void lateUpdate();

	Scene* getCurrentScene();
};
