#include <iostream>
#include <fstream>
#include "QuackEnginePro.h"
#include "FMOD_Quack.h"
#include "OgreQuack.h"
#include "PhysicsManager.h"
#include "LuaBridgeTest.h"
#include "QuackFrameListener.h"
#include "Prueba.h"
#include "LuaManager.h"
#include "PruebaFactory.h"
#include "FactoryManager.h"
#include "QuackEntity.h"
#include "RenderComponent.h"


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
		std::cout << "Tus rutas estan bien\n";
		f.close();
	}
	else
	{
		std::cerr << "ERROR: el fichero no se ha abierto, es decir, tus rutas est�n mal\n";
		std::cout << "Depuracion, directorio de trabajo, $(SolutionDir)bin\ \n";
	}

	//CargarLua();
	//CargarFMOD();
	//CargarOGRE();


	QuackEnginePro* engine = QuackEnginePro::init();
	
	engine->setup();

	engine->start();

	return 0;
}
	


	
// -------------- MOVER A OTRO ARCHIVO -------------- // 

#include "Scene.h"
	
std::unique_ptr<QuackEnginePro>  QuackEnginePro::instance_;

Scene* scene;


void QuackEnginePro::setup()
{
	ogreQuack_ = new OgreQuack();

	root_ = ogreQuack_->createRoot();

	ogreQuack_->setupRoot();

	mSM_ = ogreQuack_->getSceneManager();

	physicsManager_ = new PhysicsManager(root_, mSM_);

	fmod_quack_ = new fmod_quack();

	prueba(fmod_quack_);
	
	frameListener_ = new QuackFrameListener();

	root_->addFrameListener(frameListener_);

	//CargarLua();	

}

void QuackEnginePro::start()
{
	//crear las factorias
	addCopmponentsFactories();
	
	//crear la primera escena
	//scene = new Scene("Scenes/scene1.lua", "scene1");
	
	root_->startRendering();
}


//aqui esta el bucle del juego
void QuackEnginePro::update()
{
	//scene->update();
	physicsManager_->stepPhysics(frameListener_->deltaTime());
}



