#include "FMOD_Quack.h"
#include <assert.h>

std::unique_ptr<fmod_quack>  fmod_quack::instance_;

fmod_quack* fmod_quack::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

fmod_quack::fmod_quack(std::string route)
{
	assetsRouteFmod = route;
	
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
}

fmod_quack::~fmod_quack()
{
	for (auto soundPair : sounds_) {
		//soundPair.second->release();
		soundPair.second = nullptr;
	}
	sounds_.clear();
	for (auto dspPair : dsp_) {
		//dspPair.second->release();		
		dspPair.second = nullptr;
	}
	dsp_.clear();

	//systemFMOD_->release();				
	systemFMOD_ = nullptr;
}

fmod_quack* fmod_quack::Init(std::string route)
{
	std::cout << "Se esta inicializando FMOD\n";

	// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES (no, no?)
	assert(instance_.get() == nullptr);
	instance_.reset(new fmod_quack(route));
	return instance_.get();

	std::cout << "Se ha inicializado FMOD\n";
}

void fmod_quack::PlaySound(int channel, std::string id, float volume)
{
	auto it = Instance()->sounds_.find(id);
	if (it == Instance()->sounds_.end())
	{
		std::cout << "No se ha encontrado el sonido: " + id << "\n";
	}
	else
	{
		FMOD::Channel* channelAux;
		Instance()->systemFMOD_->getChannel(channel, &channelAux);
		Instance()->systemFMOD_->playSound(Instance()->sounds_[id], 0, false, &channelAux);
		channelAux->setVolume(volume);
	}
}


void fmod_quack::CreateSound(std::string sound, std::string id)
{
	FMOD::Sound* sonido;
	std::string path = std::string(Instance()->assetsRouteFmod + "/Sound/") + sound;
	FMOD_RESULT resultCreateSound = Instance()->systemFMOD_->createSound(path.c_str(), FMOD_DEFAULT, 0, &sonido);
	if (resultCreateSound != FMOD_OK)
	{
		std::cout << "Algo ha petado\n";
		printf("FMOD error! (%d) %s\n", resultCreateSound, FMOD_ErrorString(resultCreateSound));
		exit(-1);
	}
	Instance()->sounds_.insert(std::pair<std::string, FMOD::Sound*>(id, sonido));
}

void fmod_quack::CreateDSP(FMOD_DSP_TYPE type, std::string id)
{
	FMOD::DSP* dsp;
	FMOD_RESULT result = Instance()->systemFMOD_->createDSPByType(type, &dsp);
	if (result != FMOD_OK)
	{
		std::cout << "Algo ha petado\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	Instance()->dsp_.insert(std::pair<std::string, FMOD::DSP*>(id, dsp));
}

void fmod_quack::AddDSP(int channel, std::string isDSP)
{
	auto it = Instance()->dsp_.find(isDSP);
	if (it == Instance()->dsp_.end())
	{
		std::cout << "No se ha encontrado el sonido: " + isDSP << "\n";
	}
	else
	{
		Instance()->GetChannel(channel)->addDSP(0, Instance()->dsp_[isDSP]);
	}
}

void fmod_quack::PauseChannel(int channel, bool pause)
{
	Instance()->GetChannel(channel)->setPaused(pause);
}

void fmod_quack::StopChannel(int channel)
{
	Instance()->GetChannel(channel)->stop();
}


FMOD::Channel* fmod_quack::GetChannel(int channel)
{
	FMOD::Channel* channelAux;
	FMOD::ChannelGroup* channel_group;
	Instance()->systemFMOD_->getMasterChannelGroup(&channel_group);
	channel_group->getChannel(channel, &channelAux);
	return channelAux;
}