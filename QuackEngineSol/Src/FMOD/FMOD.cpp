#include "FMOD.h"
#include <fmod.hpp>
#include <fmod_errors.h>

Fmod::Fmod()
{
	std::cout << "Se esta inicializando FMOD\n";

	FMOD_RESULT result;
	result = FMOD::System_Create(&systemFMOD_);      // Create the main system object.
	if (result != FMOD_OK)
	{
		std::cout << "Error fmod 1\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = systemFMOD_->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		std::cout << "Error fmod 2\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	std::cout << "Se ha inicializado FMOD\n";
}

void Fmod::playSound(int channel, std::string id)
{
	auto it = sounds_.find(id);
	if (it == sounds_.end())
	{
		std::cout << "No se ha encontrado el sonido: " + id << "\n";
	}
	else
	{
		FMOD::Channel* channelAux;
		systemFMOD_->getChannel(channel, &channelAux);
		systemFMOD_->playSound(sounds_[id], 0, false, &channelAux);
	}
}


void Fmod::createSound(std::string sound, std::string id)
{
	FMOD::Sound* sonido;
	std::string path = std::string("Assets/Sound/") + sound;
	FMOD_RESULT resultCreateSound = systemFMOD_->createSound(path.c_str(), FMOD_DEFAULT, 0, &sonido);
	if (resultCreateSound != FMOD_OK)
	{
		std::cout << "Algo ha petado\n";
		printf("FMOD error! (%d) %s\n", resultCreateSound, FMOD_ErrorString(resultCreateSound));
		exit(-1);
	}
	sounds_.insert(std::pair<std::string, FMOD::Sound*>(id, sonido));
}
