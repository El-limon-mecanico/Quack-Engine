#include <iostream>
#include <fstream>
#include "FMOD_Quack.h"
#include "OGRE.h"
#include "BULLET.h"
#include "LuaBridgeTest.h"
#include "Prueba.h"
#include "LuaManager.h"
#include "PruebaFactory.h"
#include "FactoryManager.h"


//TODO cambiar esto de sitio
void addCopmponentsFactories()
{
	FactoryManager* fabricaDeManagers = new FactoryManager();
	PruebaFactory* prueba_factory = new PruebaFactory();
	fabricaDeManagers->add("Prueba", prueba_factory);
		
	Component* a = (fabricaDeManagers->create("Prueba"));
	LuaRef pruebaLuaRef = readLuaFile("prueba.lua", "prueba");
	a->init(pruebaLuaRef);
}



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
		std::cout << "Tus rutas estan bien\n";
		f.close();
	}
	else
	{
		std::cerr << "ERROR: el fichero no se ha abierto, es decir, tus rutas están mal\n";
		std::cout << "Depuracion, directorio de trabajo, $(SolutionDir)bin\ \n";
	}

	//PruebasLua();
	//CargarFMOD();
	//CargarOGRE();

	//fmod_quack* fmod_sound = new fmod_quack();
	////BULLET_Init();
	//OGRE_Init();
	//prueba(fmod_sound);

	addCopmponentsFactories();

	//while (true) {}
	return 0;
}
	
