#include <iostream>
#include <fstream>
#include "FMOD.h"
#include "Ogre_Quack.h"
#include "PhysicsManager.h"

//para que no salga la consola en el modo release (en las propiedades del proyecto hay que poner que se
//ejecute como aplicacion window no cmd (en la parte de vinculador))
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

	PhysicsManager* phyManager = new PhysicsManager(root);

	ogQuack->setupRoot();

	root->startRendering();

	FMOD_Init();

	return 0;
}
