#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <queue>

#include "Scene.h"

class QUACK_ENGINE_PRO_API SceneMng
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
	void physicsUpdate();
	void fixedUpdate();
	void update();
	void lateUpdate();
	void lastUpdate();

	Scene* getCurrentScene();
};
