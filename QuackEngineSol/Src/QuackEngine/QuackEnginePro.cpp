#include <iostream>
#include <fstream>
#include <SDL.h>
#undef main						// ESTO SE QUITA CUANDO TENGAMOS EL MAIN EN OTRO ARCHIVO
#include "QuackEnginePro.h"
#include "FMOD_Quack.h"
#include "OgreQuack.h"
#include "PhysicsManager.h"
#include "LuaBridgeTest.h"
#include "QuackFrameListener.h"

//para que no salga la consola en el modo release (en las propiedades del proyecto hay que poner que se
//ejecute como aplicacion window no cmd (en la parte de vinculador))ç



// -------------- MOVER A OTRO ARCHIVO -------------- // 

void prueba(fmod_quack* fmod_sound)
{
	fmod_sound->createSound(std::string("singing.wav"), "Cantando");
	fmod_sound->playSound(0, "Cantando", 1);
	fmod_sound->createDSP(FMOD_DSP_TYPE_ECHO, std::string("Echo"));
	fmod_sound->addDSP(0, std::string("Echo"));
	//fmod_sound->pauseChannel(0, true);
	//fmod_sound->stopChannel(0);
}

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	//esto es una prueba de los recursos
	std::ifstream f("Assets/fichero.txt");
	if (f.is_open())
	{
		std::cout << "El fichero se ha abierto\n";
		f.close();
	}
	else
	{
		std::cerr << "ERROR: el fichero no se ha abierto\n";
	}


	QuackEnginePro* engine = QuackEnginePro::init();

	engine->setup();

	engine->start();

	return 0;
}

// -------------- MOVER A OTRO ARCHIVO -------------- // 


std::unique_ptr<QuackEnginePro>  QuackEnginePro::instance_;

void QuackEnginePro::setup()
{
	ogreQuack_ = new OgreQuack();

	root_ = ogreQuack_->createRoot();

	ogreQuack_->setupRoot();

	mSM_ = ogreQuack_->getSceneManager();

	window_ = ogreQuack_->getWindow();

	sdlWindow_ = ogreQuack_->getSdlWindow();

	physicsManager_ = new PhysicsManager(root_, mSM_);

	fmod_quack_ = new fmod_quack();

	prueba(fmod_quack_);
	
	frameListener_ = new QuackFrameListener();

	root_->addFrameListener(frameListener_);

	//CargarLua();	

}

void QuackEnginePro::start()
{
	root_->startRendering();
}


void QuackEnginePro::update()
{
	pollEvents();
	physicsManager_->stepPhysics(frameListener_->deltaTime());
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
			root_->queueEndRendering();
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
