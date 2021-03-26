#include <iostream>
#include <fmod.hpp>
#include <fmod_errors.h>


void FMOD_Init()
{
	std::cout << "Aqui deberia estar cargando fmod\n";


	FMOD_RESULT result;
	FMOD::System* system = NULL;

	result = FMOD::System_Create(&system);      // Create the main system object.
	if (result != FMOD_OK)
	{
		std::cout << "Error fmod 1\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	
	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		std::cout << "Error fmod 2\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	std::cout << "Se ha inicializado FMOD?\n";
	
	FMOD::Sound* sonido;
	FMOD::Channel* channel = 0;

	FMOD_RESULT resultCreateSound = system->createSound("Assets/singing.wav", FMOD_DEFAULT,0,&sonido);
	if(resultCreateSound != FMOD_OK)
	{
		std::cout << "Algo ha petado\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	
	FMOD_RESULT resultPlaySound = system->playSound(sonido, 0, false, &channel);

	if (resultPlaySound != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	std::cout << "Se tendria que haber escuchado algo\n";
}