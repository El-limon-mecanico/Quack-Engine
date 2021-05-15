#include <iostream>
#include <fstream>
#include "QuackEnginePro.h"
#include "checkML.h"

#if (defined _DEBUG) //|| !(defined _WIN64)
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
	if (QuackEnginePro::Init()) {
		QuackEnginePro::Instance()->start();
	}

	return 0;
}
