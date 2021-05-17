#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <stack>

#include "Scene.h"

class QUACK_ENGINE_PRO_API SceneMng
{
private:
	static std::unique_ptr<SceneMng> instance_;
	
	std::stack<Scene*> sceneStack_;

	bool popScene_ = false;

	bool loadScene_ = false;

	bool pushScene_ = false;

	std::string sceneToLoad_ = "";
	std::string sceneName_ = "";

	void clearScenes();

public:

	static bool Init();
	static SceneMng* Instance();
	
	SceneMng(){}
	~SceneMng();

	void loadScene(std::string file, std::string sceneName);
	void pushNewScene(std::string file, std::string sceneName);
	void popCurrentScene();

	void preUpdate();
	void physicsUpdate();
	void fixedUpdate();
	void update();
	void lateUpdate();
	bool lastUpdate();

	Scene* getCurrentScene();
};
