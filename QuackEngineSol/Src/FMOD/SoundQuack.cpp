#include "SoundQuack.h"
#include <assert.h>
#include <fmod_errors.h>
#include <fmod.hpp>

std::unique_ptr<SoundQuack>  SoundQuack::instance_;

SoundQuack* SoundQuack::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

SoundQuack::SoundQuack(std::string route)
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

SoundQuack::~SoundQuack()
{
	sounds_.clear();
	dsp_.clear();

	//systemFMOD_->release();				
	systemFMOD_ = nullptr;
}

SoundQuack* SoundQuack::Init(std::string route)
{
	std::cout << "Se esta inicializando FMOD\n";

	// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES (no, no?)
	assert(instance_.get() == nullptr);
	instance_.reset(new SoundQuack(route));
	return instance_.get();

	std::cout << "Se ha inicializado FMOD\n";
}

void SoundQuack::playSound(FMOD::Sound* sound, float volume)
{
	auto it = std::find(sounds_.begin(), sounds_.end(), sound);
	if (it == sounds_.end())
	{
		std::cout << "No se ha encontrado el sonido" << "\n";
	}
	else
	{
		FMOD::Channel* channelAux = getChannel(sound);
		systemFMOD_->playSound(sound, NULL, false, &channelAux);
		channelAux->setVolume(volume);
		channels_[sound] = channelAux;
	}
}

void SoundQuack::setMode(FMOD::Sound* sound, int flags) {
	getChannel(sound)->setMode(flags);
	sound->setMode(flags);
}

FMOD::FMOD_MODE SoundQuack::getMode(FMOD::Sound* sound) {
	FMOD::FMOD_MODE mode = NULL;
	getChannel(sound)->getMode(&mode);
	return mode;
}

FMOD::Sound* SoundQuack::createSound(std::string sound, int flags)
{
	FMOD::Sound* sonido;
	std::string path = std::string(assetsRouteFmod + "/Sound/") + sound;
	FMOD_RESULT resultCreateSound = systemFMOD_->createSound(path.c_str(), flags, 0, &sonido);
	if (resultCreateSound != FMOD_OK)
	{
		printf("ERROR: FMOD error! (%d) %s\n", resultCreateSound, FMOD_ErrorString(resultCreateSound));
		return nullptr;
	}
	else sounds_.push_back(sonido);
	return sonido;
}

void SoundQuack::create3DSound(std::string sound) { createSound(sound, FMOD_3D); }

void SoundQuack::removeSound(FMOD::Sound* sound)
{
	stopSound(sound);
	channels_.erase(sound);
	auto it = std::find(sounds_.begin(), sounds_.end(), sound);
	if (it != sounds_.end())
		sounds_.erase(it);
}

int SoundQuack::createDSP(FMOD_DSP_TYPE type, std::string id)
{
	FMOD::DSP* dsp;
	FMOD_RESULT result = systemFMOD_->createDSPByType(type, &dsp);
	if (result != FMOD_OK)
	{
		printf("ERROR: FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return -1;
	}
	else dsp_.insert(std::pair<std::string, FMOD::DSP*>(id, dsp));

	return currentChannel++;
}

void SoundQuack::addDSP(FMOD::Sound* sound, std::string idDSP)
{
	auto it = dsp_.find(idDSP);
	if (it == dsp_.end()) {
		std::cout << "No se ha encontrado el sonido: " + idDSP << "\n";
	}
	else {
		getChannel(sound)->addDSP(0, dsp_[idDSP]);
	}
}

void SoundQuack::pauseSound(FMOD::Sound* sound, bool pause)
{
	getChannel(sound)->setPaused(pause);
}

bool SoundQuack::isPlaying(FMOD::Sound* sound)
{
	bool b;
	if (getChannel(sound)->isPlaying(&b) == FMOD_ERR_INVALID_HANDLE)
		return false;
	return b;
}

void SoundQuack::stopSound(FMOD::Sound* sound)
{
	getChannel(sound)->stop();
}

void SoundQuack::loop(FMOD::Sound* sound, int times)
{
	getChannel(sound)->setLoopCount(times);
	sound->setLoopCount(times);
}

int SoundQuack::getCurrentLoop(FMOD::Sound* sound)
{
	int current;
	getChannel(sound)->getLoopCount(&current);
	return current;
}

void SoundQuack::setVolume(FMOD::Sound* sound, float volume)
{
	getChannel(sound)->setVolume(volume);
}

float SoundQuack::getVolume(FMOD::Sound* sound)
{
	float volume;
	getChannel(sound)->getVolume(&volume);
	return volume;
}


FMOD::Channel* SoundQuack::getChannel(FMOD::Sound* sound)
{
	return channels_[sound];
}