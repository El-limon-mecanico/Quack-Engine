#include "SceneMng.h"

SceneMng::SceneMng()
{
}

SceneMng::~SceneMng()
{
	//eliminamos todas las escenas que podría haber cargadas
	while(!sceneQueue_.empty())
	{
		delete sceneQueue_.front();
		sceneQueue_.pop();
	}
}

void SceneMng::loadScene(std::string file, std::string sceneName)
{
	sceneQueue_.push(new Scene(file, sceneName));
}

void SceneMng::preUpdate()
{
	sceneQueue_.front()->preUpdate();
}

void SceneMng::update()
{
	sceneQueue_.front()->update();
}

void SceneMng::lateUpdate()
{
	sceneQueue_.front()->lateUpdate();
}

Scene* SceneMng::getCurrentScene()
{
	return sceneQueue_.front();
}
