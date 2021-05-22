#include <OgreRoot.h>
#include <SDL_video.h>
#include <SDL_events.h>
#include <assert.h>
#include <fstream>
#include <string>

#include "QuackEnginePro.h"
#include "SoundQuack.h"
#include "OgreQuack.h"
#include "BulletQuack.h"
#include "LuaBridgeTest.h"
#include "checkML.h"
#include "LuaManager.h"
#include "FactoryManager.h"
#include "QuackEntity.h"
#include "QuackTime.h"
#include "CEGUIQuack.h"

#include "Scene.h"
#include "SceneMng.h"
#include "ResourceMng.h"

#include "InputManager.h"
#include "SDL_scancode.h"
#include "SDL_video.h"

#include "CallBacks.h"


void QuackEnginePro::readAssetsRoute()
{
	std::ifstream file;
	try
	{
		file.open("AssetsRoute.txt");
		std::getline(file, assets_route);
		file.close();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR: no se ha podido abrir el archivo de especificación de la ruta de assets\n";
	}
}



std::unique_ptr<QuackEnginePro>  QuackEnginePro::instance_;

QuackEnginePro::~QuackEnginePro() {
	delete quackTime_;	quackTime_ = nullptr;
};

bool QuackEnginePro::Init(std::string name)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	assert(instance_.get() == nullptr);
	instance_.reset(new QuackEnginePro(name));
	return instance_.get();
}

QuackEnginePro* QuackEnginePro::Instance() {
	assert(instance_.get() != nullptr);
	return instance_.get();
}

void QuackEnginePro::setup()
{
	readAssetsRoute();

	OgreQuack::Init(windowName);

	ResourceMng::Init(assets_route);
	ResourceMng::Instance()->setup(); //Carga de recursos

	sdlWindow_ = OgreQuack::Instance()->getSdlWindow();

	QuackEntity::Init();

	BulletQuack::Init();

	SoundQuack::Init(assets_route);
	//SoundQuack::Instance()->createSound("singing.wav", "singing");	sound test

	FactoryManager::Init();

	CEGUIQuack::Init();
	CEGUIQuack::Instance()->setUp(OgreQuack::Instance()->getWindow());

	CallBacks::Init();

	SceneMng::Init();

	InputManager::Init();
}

void QuackEnginePro::start(std::string route, std::string name)
{
	SceneMng::Instance()->loadScene(route, name);
	//setFullScreen(true);
	if (!updateStarted) {
		quackTime_ = new QuackTime();
		update();
	}
}


void QuackEnginePro::update()
{
	exit = false;

	while (!exit) {

		quackTime_->frameStarted();

		fixedTime += time()->deltaTime();

		SceneMng::Instance()->preUpdate();

		BulletQuack::Instance()->stepPhysics(time()->deltaTime(), FIXED_TIME_UPDATE);

		SceneMng::Instance()->physicsUpdate();

		pollEvents();

		if (fixedTime > FIXED_TIME_UPDATE) {
			SceneMng::Instance()->fixedUpdate();
			fixedTime = 0;
		}

		SceneMng::Instance()->update(); //actualizamos la escena que actualiza las entidades	

		OgreQuack::Instance()->getRoot()->renderOneFrame();

		SceneMng::Instance()->lateUpdate();

		//CEGUIQuack::Instance()->render(time()->deltaTime());

		if (!SceneMng::Instance()->lastUpdate())
			exit = true;
	}
}


void QuackEnginePro::pollEvents()
{
	if (sdlWindow_ == nullptr)
		return;  // SDL events not initialized
	SDL_Event event;
	InputManager::Instance()->flushInput();
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			OgreQuack::Instance()->getRoot()->queueEndRendering();
			exit = true;
			break;
		default:
			InputManager::Instance()->ManageInput(event);
			break;
		}
	}
}

QuackTime* QuackEnginePro::time()
{
	return quackTime_;
}

void QuackEnginePro::setFullScreen(bool set)
{
	OgreQuack::Instance()->setFullScreen(set);
	CEGUIQuack::Instance()->resizeWindow(OgreQuack::Instance()->getWindowW(), OgreQuack::Instance()->getWindowH());
}

void QuackEnginePro::setWindowSize(int width, int height)
{
	OgreQuack::Instance()->setResolution(width, height);
	CEGUIQuack::Instance()->resizeWindow(width, height);
}

int QuackEnginePro::getWindoWidth()
{
	return OgreQuack::Instance()->getWindowW();
}

int QuackEnginePro::getWindoHeight()
{
	return OgreQuack::Instance()->getWindowH();
}
