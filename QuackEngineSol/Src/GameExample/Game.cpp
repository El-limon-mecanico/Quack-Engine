#include <iostream>
#include <fstream>
#include "QuackEnginePro.h"


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

	// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
	if (QuackEnginePro::Init()) {
		QuackEnginePro::Instance()->start();
	}


	return 0;
}
