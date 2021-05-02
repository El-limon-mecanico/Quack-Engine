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
#include "Transform.h"
#include "LuaManager.h"
#include "FactoryManager.h"
#include "QuackEntity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"

#include "Scene.h"
#include "SceneMng.h"
#include "ResourceMng.h"

//para que no salga la consola en el modo release (en las propiedades del proyecto hay que poner que se
//ejecute como aplicacion window no cmd (en la parte de vinculador))ç

//TODO cambiar esto de sitio
void addComponentsFactories()
{
	FactoryManager::init();

	FactoryManager::instance()->add<MeshRenderer>();
	FactoryManager::instance()->add<Rigidbody>();
	FactoryManager::instance()->add<Prueba>();
	FactoryManager::instance()->add<Transform>();
}



// TODO -------------- MOVER A OTRO ARCHIVO -------------- // 
void QuackEnginePro::prueba()
{
	QuackEntity* plane = new QuackEntity("PlanoToGuapo");
	MeshRenderer* r = plane->addComponent<MeshRenderer>();
	r->setMeshByPrefab(PrefabType::PT_PLANE); //:)))
	Rigidbody* rb = plane->addComponent<Rigidbody>();

	r->getNode()->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(Ogre::Degree(-90)));
	r->getNode()->scale(5, 5, 1);
	r->getNode()->setPosition(0, -300, 0);

	rb->setRigidbody(0, ColliderType::CT_BOX);
	
	SceneMng::Instance()->getCurrentScene()->addEntity(plane);
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
	quackTime_ = new QuackTime();

	OgreQuack::Init();
	OgreQuack::Instance()->createRoot();
	OgreQuack::Instance()->setupRoot();

	ResourceMng::Init(); 
	ResourceMng::Instance()->setup(); //Carga de recursos

	sdlWindow_ = OgreQuack::Instance()->getSdlWindow();

	BulletQuack::Init();

	fmod_quack_ = new fmod_quack();

	addComponentsFactories();

	SceneMng::Init();
	SceneMng::Instance()->loadScene("Scenes/scene1.lua", "scene1");
}

void QuackEnginePro::start()
{
	if (!updateStarted) {
		prueba();
		update();
	}
}


void QuackEnginePro::update()
{
	exit = false;
	while (!exit) {
		quackTime_->frameStarted();

		SceneMng::Instance()->preUpdate();

		BulletQuack::Instance()->stepPhysics(time()->deltaTime());

		pollEvents();

		SceneMng::Instance()->update(); //actualizamos la escena que actualiza las entidades	

		OgreQuack::Instance()->getRoot()->renderOneFrame();

		SceneMng::Instance()->lateUpdate();
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
			//llamar a InputManager
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