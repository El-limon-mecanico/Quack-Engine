#include <iostream>
#include <fstream>
#include "FMOD.h"
//#include "OGRE.h"
#include "LuaBridgeTest.h"

int main()
{
	//esto es una prueba de los recursos
	std::ifstream f("Assets/fichero.txt");
	if(f.is_open())
	{
		std::cout << "El fichero se ha abierto\n";
		f.close();
	}
	else
	{
		std::cerr << "ERROR: el fichero no se ha abierto\n";
	}

	CargarLua();
	//CargarFMOD();
	//CargarOGRE();


	return 0;
}