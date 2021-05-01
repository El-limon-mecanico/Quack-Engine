#include "SceneMng.h"
#include "checkML.h"

std::unique_ptr<SceneMng> SceneMng::instance_;

SceneMng::~SceneMng()
{
	//eliminamos todas las escenas que podría haber cargadas
	while(!sceneQueue_.empty())
	{
		delete sceneQueue_.front();
		sceneQueue_.pop();
	}
}

bool SceneMng::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new SceneMng());
	return instance_.get();
}

SceneMng* SceneMng::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

void SceneMng::loadScene(std::string file, std::string sceneName)
{
	sceneQueue_.push(new Scene(file, sceneName));
}

void SceneMng::preUpdate()
{
	sceneQueue_.front()->preUpdate();
}

void SceneMng::physicsUpdate()
{
	sceneQueue_.front()->physicsUpdate();
}

void SceneMng::fixedUpdate()
{
	sceneQueue_.front()->fixedUpdate();
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
