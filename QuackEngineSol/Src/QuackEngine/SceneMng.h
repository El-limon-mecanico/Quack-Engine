#pragma once
#include <queue>

#include "Scene.h"

class SceneMng
{
private:
	static std::unique_ptr<SceneMng> instance_;
	
	std::queue<Scene*> sceneQueue_;

public:

	static bool Init();
	static SceneMng* Instance();
	
	SceneMng(){}
	~SceneMng();

	void loadScene(std::string file, std::string sceneName);

	void preUpdate();
	void update();
	void lateUpdate();

	Scene* getCurrentScene();
};
