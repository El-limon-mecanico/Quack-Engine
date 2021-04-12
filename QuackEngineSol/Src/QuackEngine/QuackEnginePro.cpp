#include <iostream>
#include <fstream>
#include "QuackEnginePro.h"
#include "FMOD_Quack.h"
#include "Ogre_Quack.h"
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

	Ogre_Quack* ogQuack = new Ogre_Quack();

	Ogre::Root* root = ogQuack->createRoot();

	PhysicsManager* py = new PhysicsManager(root);

	ogQuack->setupRoot();

	fmod_quack* fmod_sound = new fmod_quack();
	prueba(fmod_sound);

	//CargarLua();

	root->startRendering();

	return 0;
}

// -------------- MOVER A OTRO ARCHIVO -------------- // 

