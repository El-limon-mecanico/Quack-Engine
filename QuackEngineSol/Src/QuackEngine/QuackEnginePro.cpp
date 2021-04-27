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
#include "Prueba.h"
#include "LuaManager.h"
#include "FactoryManager.h"
#include "QuackEntity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "BtOgre.h"

#include "Scene.h"

//para que no salga la consola en el modo release (en las propiedades del proyecto hay que poner que se
//ejecute como aplicacion window no cmd (en la parte de vinculador))ç

//TODO cambiar esto de sitio
void addCopmponentsFactories()
{
	FactoryManager::init();

	FactoryManager::instance()->add<MeshRenderer>("MeshRenderer");
	FactoryManager::instance()->add<Rigidbody>("Rigidbody");
	FactoryManager::instance()->add<Prueba>("Prueba");
}



// -------------- MOVER A OTRO ARCHIVO -------------- // 

void QuackEnginePro::prueba()
{
	/*fmod_quack_->createSound(std::string("song.wav"), "Cantando");
	fmod_quack_->playSound(0, "Cantando", 1);
	fmod_quack_->createDSP(FMOD_DSP_TYPE_ECHO, std::string("Echo"));*/
	//fmod_sound->addDSP(0, std::string("Echo"));
	//fmod_sound->pauseChannel(0, true);
	//fmod_sound->stopChannel(0);

	//QuackEntity* sphere1 = new QuackEntity();
	//Render* r = sphere1->addComponent<Render>();
	//r->setMeshByPrefab(PrefabType::PT_SPHERE); //:)
	//Rigidbody* rb = sphere1->addComponent<Rigidbody>();
	////sphere1->getNode()->setPosition(0, 300, 0);

	//rb->setRigidbody(1, ColliderType::CT_SPHERE);

	//QuackEntity* sphere2 = new QuackEntity();
	//r = sphere2->addComponent<Render>();
	//r->setMeshByPrefab(PrefabType::PT_SPHERE); //:)))
	//rb = sphere2->addComponent<Rigidbody>();
	//sphere2->getNode()->setPosition(50, 500, 0);

	//rb->setRigidbody(1, ColliderType::CT_SPHERE);

	//QuackEntity* plane = new QuackEntity();
	//r = plane->addComponent<Render>();
	//r->setMeshByPrefab(PrefabType::PT_PLANE); //:)))
	//rb = plane->addComponent<Rigidbody>();

	//plane->getNode()->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(Ogre::Degree(-90)));
	//plane->getNode()->scale(5, 5, 1);

	//rb->setRigidbody(0, ColliderType::CT_BOX);
	//rb->getRigidbody()->setGravity(btVector3(0, 0, 0));
	//rb->setRigidbody(0);
// 	rb->getRigidbody()->setGravity(btVector3(0, 0, 0));

// 	scene_->addEntity(sphere1);
// 	scene_->addEntity(sphere2);
// 	scene_->addEntity(plane);
	// rb->setRigidbody(0);
	// rb->getRigidbody()->setGravity(btVector3(0, 0, 0));

	// scene_->addEntity(sphere1);
	// scene_->addEntity(sphere2);
	// scene_->addEntity(plane);
}

std::unique_ptr<QuackEnginePro>  QuackEnginePro::instance_;

// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
bool QuackEnginePro::Init()
{
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

	sdlWindow_ = OgreQuack::Instance()->getSdlWindow();

	BulletQuack::Init();

	fmod_quack_ = new fmod_quack();

	addCopmponentsFactories();

	scene_ = new Scene("Scenes/scene1.lua", "scene1");  // NECESITAMOS UN SCENE MANAGER QUE GUARDE LAS ESCENAS Y LAS MANEJE 
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

		scene_->preUpdate();

		BulletQuack::Instance()->stepPhysics(time()->deltaTime());

		pollEvents();

		scene_->update(); //actualizamos la escena que actualiza las entidades	

		OgreQuack::Instance()->getRoot()->renderOneFrame();

		scene_->lateUpdate();
	}
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