#include "FMOD_Quack.h"


fmod_quack::fmod_quack()
{
	FMOD_Init();
}

void fmod_quack::FMOD_Init()
{
	std::cout << "Se esta inicializando FMOD\n";

	FMOD_RESULT result;
	result = FMOD::System_Create(&systemFMOD_);      // Create the main system object.
	if (result != FMOD_OK)
	{
		std::cout << "Error fmod_quack 1\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = systemFMOD_->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		std::cout << "Error fmod_quack 2\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	std::cout << "Se ha inicializado FMOD\n";
}

void fmod_quack::playSound(int channel, std::string id, float volume)
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
		channelAux->setVolume(volume);
	}
}


void fmod_quack::createSound(std::string sound, std::string id)
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

void fmod_quack::createDSP(FMOD_DSP_TYPE type, std::string id)
{
	FMOD::DSP* dsp;
	FMOD_RESULT result = systemFMOD_->createDSPByType(type, &dsp);
	if (result != FMOD_OK)
	{
		std::cout << "Algo ha petado\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	dsp_.insert(std::pair<std::string, FMOD::DSP*>(id, dsp));
}

void fmod_quack::addDSP(int channel, std::string isDSP)
{
	auto it = dsp_.find(isDSP);
	if (it == dsp_.end())
	{
		std::cout << "No se ha encontrado el sonido: " + isDSP << "\n";
	}
	else
	{
		FMOD::Channel* channelAux;
		FMOD::ChannelGroup* channel_group;
		systemFMOD_->getMasterChannelGroup(&channel_group);
		channel_group->getChannel(channel, &channelAux);
		channelAux->addDSP(0, dsp_[isDSP]);
	}
}

void fmod_quack::pauseChannel(int channel, bool pause)
{
	FMOD::Channel* channelAux;
	FMOD::ChannelGroup* channel_group;
	systemFMOD_->getMasterChannelGroup(&channel_group);
	channel_group->getChannel(channel, &channelAux);
	channelAux->setPaused(pause);
}
