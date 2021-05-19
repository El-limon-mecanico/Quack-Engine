#include "SceneMng.h"
#include "checkML.h"
#include <OgreQuack.h>
#include <OgreSceneManager.h>

std::unique_ptr<SceneMng> SceneMng::instance_;

SceneMng::~SceneMng()
{
	clearScenes();
}

void SceneMng::clearScenes()
{
	while (!sceneStack_.empty())
	{
		delete sceneStack_.top();
		sceneStack_.pop();
	}
	//OgreQuack::Instance()->getSceneManager()->clearScene();
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
	if (sceneStack_.empty()) {
		Scene* scene = new Scene(file, sceneName);
		sceneStack_.push(scene);
		scene->start();
	}
	else {
		loadScene_ = true;
		sceneName_ = sceneName;
		sceneToLoad_ = file;
	}
}

void SceneMng::pushNewScene(std::string file, std::string sceneName)
{
	pushScene_ = true;
	sceneName_ = sceneName;
	sceneToLoad_ = file;
}

void SceneMng::popCurrentScene()
{
	popScene_ = true;
}

void SceneMng::preUpdate()
{
	if (!sceneStack_.empty())
		sceneStack_.top()->preUpdate();
}

void SceneMng::physicsUpdate()
{
	if (!sceneStack_.empty())
		sceneStack_.top()->physicsUpdate();
}

void SceneMng::fixedUpdate()
{
	if (!sceneStack_.empty())
		sceneStack_.top()->fixedUpdate();
}

void SceneMng::update()
{
	if (!sceneStack_.empty())
		sceneStack_.top()->update();
}

void SceneMng::lateUpdate()
{
	if (!sceneStack_.empty())
		sceneStack_.top()->lateUpdate();
}

bool SceneMng::lastUpdate()
{
	if (!sceneStack_.empty()) {
		sceneStack_.top()->lastUpdate();
		if (popScene_) {
			delete sceneStack_.top();
			sceneStack_.pop();
			popScene_ = false;
		}
		else if (loadScene_ || pushScene_) {
			if (loadScene_)
				clearScenes();
			Scene* scene = new Scene(sceneToLoad_, sceneName_);
			sceneStack_.push(scene);
			scene->start();
			loadScene_ = false;
			pushScene_ = false;
		}
		return true;
	}
	else
		return false;
}

Scene* SceneMng::getCurrentScene()
{
	return sceneStack_.top();
}
