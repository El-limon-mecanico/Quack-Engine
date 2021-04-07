#include <iostream>
#include <fstream>
#include "FMOD_Quack.h"
#include "OGRE.h"
#include "BULLET.h"

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

	fmod_quack* fmod_sound = new fmod_quack();
	BULLET_Init();
	OGRE_Init();
	prueba(fmod_sound);
	while (true);

	return 0;
}
