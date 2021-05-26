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

SoundQuack::SoundQuack(std::string route) :
	listeners_(std::vector<bool>(FMOD_MAX_LISTENERS, false)),
	channels_(std::map<FMOD::Sound*, FMOD::Channel*>())
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

	result = systemFMOD_->init(512, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		std::cout << "Error fmod_quack 2\n";
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

SoundQuack::~SoundQuack()
{
	channels_.clear();
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
	auto it = channels_.find(sound);
	if (it == channels_.end())
	{
		std::cout << "No se ha encontrado el sonido" << "\n";
	}
	else
	{
		FMOD::Channel* channelAux;
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

void SoundQuack::updateListener(int index, FMOD_VECTOR listenerPos, FMOD_VECTOR listenerFW, FMOD_VECTOR listenerUP, FMOD_VECTOR listenerVel)
{
	systemFMOD_->set3DListenerAttributes(index, &listenerPos, &listenerVel, &listenerFW, &listenerUP);     // update 'ears
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
	else channels_[sonido] = nullptr;
	return sonido;
}

void SoundQuack::removeSound(FMOD::Sound* sound)
{
	stopSound(sound);
	channels_.erase(sound);
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

void SoundQuack::set3DTransform(FMOD::Sound* sound, FMOD_VECTOR soundPos, FMOD_VECTOR soundVel)
{
	getChannel(sound)->set3DAttributes(&soundPos, &soundVel);
}

void SoundQuack::update()
{
	systemFMOD_->update();   // needed to update 3d engine, once per frame.
}


FMOD::Channel* SoundQuack::getChannel(FMOD::Sound* sound)
{
	return channels_[sound];
}

int SoundQuack::getNewListener()
{
	int i = 0;

	for(int i = 0; i < listeners_.size(); i++){
		if (!listeners_[i]){
			listeners_[i] = true;
			return i;
		}
	}
	return -1;
}

void SoundQuack::removeListener(int index)
{
	listeners_[index] = false;
	updateListener(index, { 10000,10000,10000 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}