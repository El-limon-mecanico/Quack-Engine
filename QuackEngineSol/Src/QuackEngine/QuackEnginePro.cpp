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
#include "PruebaFactory.h"
#include "LuaManager.h"
#include "FactoryManager.h"
#include "QuackEntity.h"
#include "RenderComponent.h"
#include "QuackTime.h"


//para que no salga la consola en el modo release (en las propiedades del proyecto hay que poner que se
//ejecute como aplicacion window no cmd (en la parte de vinculador))ç

//TODO cambiar esto de sitio
void addCopmponentsFactories()
{
	FactoryManager::init();
	
	PruebaFactory* prueba_factory = new PruebaFactory();
	FactoryManager::instance()->add("prueba", prueba_factory);

}



// -------------- MOVER A OTRO ARCHIVO -------------- // 

void prueba(fmod_quack* fmod_sound)
{
	fmod_sound->createSound(std::string("song.wav"), "Cantando");
	fmod_sound->playSound(0, "Cantando", 1);
	fmod_sound->createDSP(FMOD_DSP_TYPE_ECHO, std::string("Echo"));
	//fmod_sound->addDSP(0, std::string("Echo"));
	//fmod_sound->pauseChannel(0, true);
	//fmod_sound->stopChannel(0);
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
	
#include "Scene.h"

Scene* scene;


void QuackEnginePro::setup()
{
	quackTime_ = new QuackTime();

	OgreQuack::Init();

	OgreQuack::Instance()->createRoot();

	OgreQuack::Instance()->setupRoot();

	sdlWindow_ = OgreQuack::Instance()->getSdlWindow();

	BulletQuack::Init(OgreQuack::Instance()->getRoot(), OgreQuack::Instance()->getSceneManager());

	fmod_quack_ = new fmod_quack();

	prueba(fmod_quack_);

	//CargarLua();	

}

void QuackEnginePro::start()
{
	if (!updateStarted){
        addCopmponentsFactories();
        update();
    } 
    
}


void QuackEnginePro::update()
{
	exit = false;
	while (!exit) {
		quackTime_->frameStarted();
		OgreQuack::Instance()->getRoot()->renderOneFrame();
		pollEvents();
		BulletQuack::Instance()->stepPhysics(time()->deltaTime());
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