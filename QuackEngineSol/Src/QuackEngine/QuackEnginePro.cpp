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


//TODO cambiar esto de sitio
void addCopmponentsFactories()
{
	FactoryManager* f =	FactoryManager::init();

	
	PruebaFactory* prueba_factory = new PruebaFactory();
	FactoryManager::instance()->add("Prueba", prueba_factory);
	
		
	Component* a = (FactoryManager::instance()->instance()->create("Prueba"));
	LuaRef pruebaLuaRef = readLuaFile("prueba.lua", "prueba");
	a->init(pruebaLuaRef);
}



//para que no salga la consola en el modo release (en las propiedades del proyecto hay que poner que se
//ejecute como aplicacion window no cmd (en la parte de vinculador))�

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

	addCopmponentsFactories();
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
	physicsManager_->stepPhysics(frameListener_->deltaTime());
}
