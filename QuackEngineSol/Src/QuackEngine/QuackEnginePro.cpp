#define QUACK_ENGINE_PRO_EXPORT
#include <OgreRoot.h>
#include <SDL_video.h>
#include <SDL_events.h>
#include <memory>
#include <assert.h>
#include "QuackEnginePro.h"
#include "FMOD_Quack.h"
#include "OgreQuack.h"
#include "BulletQuack.h"
#include "LuaBridgeTest.h"
#include "checkML.h"
#include "Prueba.h"
#include "Prueba2.h"
#include "Transform.h"
#include "LuaManager.h"
#include "FactoryManager.h"
#include "QuackEntity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "QuackTime.h"
#include "CEGUIQuack.h"
#include "QuackCamera.h"
#include "Light.h"

#include "Scene.h"
#include "SceneMng.h"
#include "ResourceMng.h"

#include "InputManager.h"
#include "SDL_scancode.h"

//para que no salga la consola en el modo release (en las propiedades del proyecto hay que poner que se
//ejecute como aplicacion window no cmd (en la parte de vinculador))ç

//TODO cambiar esto de sitio
void addComponentsFactories()
{
	FactoryManager::init();

	FactoryManager::instance()->add<MeshRenderer>();
	FactoryManager::instance()->add<Rigidbody>();
	FactoryManager::instance()->add<Prueba>();
	FactoryManager::instance()->add<Prueba2>();
	FactoryManager::instance()->add<Transform>();
	FactoryManager::instance()->add<QuackCamera>();
	FactoryManager::instance()->add<Light>();
}



// TODO -------------- MOVER A OTRO ARCHIVO -------------- // 
void QuackEnginePro::prueba()
{

	QuackEntity* cube = new QuackEntity("Cubito");
	MeshRenderer* r = cube->addComponent<MeshRenderer>();
	r->setMeshByPrefab(PrefabType::PT_CUBE); //:)))
	cube->addComponent<Prueba2>();

	QuackEntity* mono = new QuackEntity("Mono");
	r = mono->addComponent<MeshRenderer>();
	r->setMeshByName("Suzanne.mesh");
	mono->addComponent<Prueba2>();

	SceneMng::Instance()->getCurrentScene()->addEntity(cube);
	mono->setActive(true);
	SceneMng::Instance()->getCurrentScene()->addEntity(mono);

	mono->transform()->setLocalPosition({ -10,0,-10 });
	cube->transform()->setLocalPosition({ -10,5,-10 });

	cube->transform()->setParent(mono->transform());

	mono->transform()->Rotate({ -90,0,0 });

	CEGUIQuack::Instance()->loadScheme("AlfiskoSkin.scheme");
	CEGUIQuack::Instance()->createWidget("AlfiskoSkin/Button", "test");
}
// -------------- MOVER A OTRO ARCHIVO -------------- // 




std::unique_ptr<QuackEnginePro>  QuackEnginePro::instance_;

QuackEnginePro::~QuackEnginePro() {
	delete fmod_quack_; fmod_quack_ = nullptr;
	delete quackTime_;	quackTime_ = nullptr;
};

// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES (you sure¿?)
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
	OgreQuack::Init();

	ResourceMng::Init();
	ResourceMng::Instance()->setup(); //Carga de recursos

	sdlWindow_ = OgreQuack::Instance()->getSdlWindow();

	QuackEntity::Init();

	BulletQuack::Init();

	fmod_quack_ = new fmod_quack();

	addComponentsFactories();

	CEGUIQuack::Init();
	CEGUIQuack::Instance()->setUp(OgreQuack::Instance()->getWindow());

	//CargarLua();
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
	int frames = 0;
	double t = 0;
	while (!exit) {
		frames++;
		t += time()->deltaTime();
		if (t >= 1) {
			std::cout << "Last second frames: " << frames << "\n";
			t = 0;
			frames = 0;
		}

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

		CEGUIQuack::Instance()->draw();
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