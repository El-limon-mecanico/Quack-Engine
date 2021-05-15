#include <OgreRoot.h>
#include <SDL_video.h>
#include <SDL_events.h>
#include <assert.h>
#include <fstream>
#include <string>

#include "QuackEnginePro.h"
#include "FMOD_Quack.h"
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


void QuackEnginePro::pruebaBotonCallback()
{
	std::cout << "Se ha presionado el boton\n";
}


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

void QuackEnginePro::prueba()
{
	CEGUIQuack::Instance()->createButton("Button", "Betis", { 0.5,0.5 }, { 100,100}, 
		pruebaBotonCallback);
	
	CEGUIQuack::Instance()->createImage("Cuchao", "cuchao.png", { 0.1,0.6 }, { 300,200 });
	CEGUIQuack::Instance()->createText("Texto", "Esto no es un boton, es solo texto", { 0.5, 0.05 }, { 270, 50 });
}



std::unique_ptr<QuackEnginePro>  QuackEnginePro::instance_;

QuackEnginePro::~QuackEnginePro() {
	delete fmod_quack_; fmod_quack_ = nullptr;
	delete quackTime_;	quackTime_ = nullptr;
};

bool QuackEnginePro::Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#if (defined _DEBUG) && (defined _WIN32)
	int* a = new int();		// para que estemos seguros de que siempre se estan viendo los memory leaks
#endif

	assert(instance_.get() == nullptr);
	instance_.reset(new QuackEnginePro());
	return instance_.get();
}

QuackEnginePro* QuackEnginePro::Instance()
{
	assert(instance_.get() != nullptr);
	
	return instance_.get();
}

void QuackEnginePro::setup()
{
	readAssetsRoute();
	
	OgreQuack::Init();

	ResourceMng::Init(assets_route);
	ResourceMng::Instance()->setup(); //Carga de recursos

	sdlWindow_ = OgreQuack::Instance()->getSdlWindow();

	QuackEntity::Init();

	BulletQuack::Init();

	fmod_quack_ = new fmod_quack(assets_route);

	FactoryManager::Init();

	CEGUIQuack::Init();
	CEGUIQuack::Instance()->setUp(OgreQuack::Instance()->getWindow());
	
	
	SceneMng::Init();
	SceneMng::Instance()->loadScene("Scenes/scene1.lua", "scene1");

	InputManager::Init();
}

void QuackEnginePro::start()
{
	if (!updateStarted) {
		prueba();
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
		
		SceneMng::Instance()->lastUpdate();
		CEGUIQuack::Instance()->render(time()->deltaTime());
	}

#if (defined _DEBUG) || !(defined _WIN32)
	std::cout << "WARNING: Deberia haber al menos 4 bytes de basura\n";
#endif
}


void QuackEnginePro::pollEvents()
{
	if (sdlWindow_ == nullptr)
		return;  // SDL events not initialized
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			OgreQuack::Instance()->getRoot()->queueEndRendering();
			exit = true;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.windowID == SDL_GetWindowID(sdlWindow_)) {
				/*if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Ogre::RenderWindow* win = window;
					win->windowMovedOrResized();
					frameListener_->windowResized(win);
				}*/
			}
			break;
		default:
			InputManager::Instance()->ManageInput(event);
			if (InputManager::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) std::cout << "INPUT MANAGER PULSANDO EL ESPACIO";
			break;
		}
	}
}

fmod_quack* QuackEnginePro::getFmodQuack()
{
	return fmod_quack_;
}

QuackTime* QuackEnginePro::time()
{
	return quackTime_;
}