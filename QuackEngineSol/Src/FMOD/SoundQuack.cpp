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

SoundQuack* SoundQuack::Init(std::string route)
{
	std::cout << "Se esta inicializando FMOD\n";

	// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES (no, no?)
	assert(instance_.get() == nullptr);
	instance_.reset(new SoundQuack(route));
	return instance_.get();

	std::cout << "Se ha inicializado FMOD\n";
}

void SoundQuack::playChannel(int channel, std::string id, float volume)
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
		systemFMOD_->playSound(sounds_[id], NULL, false, &channelAux);
		channelAux->setVolume(volume);
	}
}

void SoundQuack::setMode(int channel, int flags, std::string& id) {
	getChannel(channel)->setMode(flags);
	auto soundit = sounds_.find(id);
	if (soundit != sounds_.end()) {
		FMOD::Sound* sound = (*soundit).second;
		sound->setMode(flags);
	}
}

FMOD::FMOD_MODE SoundQuack::getMode(int channel) {
	FMOD::FMOD_MODE mode=NULL;
	getChannel(channel)->getMode(&mode);
	return mode;
}

int SoundQuack::createSound(std::string sound, std::string id, int flags)
{
	FMOD::Sound* sonido;
	std::string path = std::string(assetsRouteFmod + "/Sound/") + sound;
	FMOD_RESULT resultCreateSound = systemFMOD_->createSound(path.c_str(), flags, 0, &sonido);
	if (resultCreateSound != FMOD_OK)
	{
		printf("ERROR: FMOD error! (%d) %s\n", resultCreateSound, FMOD_ErrorString(resultCreateSound));
		return -1;
	}
	else sounds_.insert(std::pair<std::string, FMOD::Sound*>(id, sonido));
	
	return currentChannel++;
}

int SoundQuack::create3DSound(std::string sound, std::string id) {		return createSound(sound, id, FMOD_3D);		}

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

void SoundQuack::addDSP(int channel, std::string idDSP)
{
	auto it = dsp_.find(idDSP);
	if (it == dsp_.end()) {
		std::cout << "No se ha encontrado el sonido: " + idDSP << "\n";
	}
	else {
		getChannel(channel)->addDSP(0, dsp_[idDSP]);
	}
}

void SoundQuack::pauseChannel(int channel, bool pause)
{
	getChannel(channel)->setPaused(pause);
}

bool SoundQuack::isPlaying(int channel)
{
	bool b;
	if (getChannel(channel)->isPlaying(&b) == FMOD_ERR_INVALID_HANDLE)
		return false;
	return b;
}

void SoundQuack::stopChannel(int channel)
{
	getChannel(channel)->stop();
}

void SoundQuack::loop(int channel, int times, std::string& id)
{
	getChannel(channel)->setLoopCount(times);
	auto soundit = sounds_.find(id);
	if (soundit != sounds_.end()) {
		FMOD::Sound* sound = (*soundit).second;
		sound->setLoopCount(times);
	}
}

int SoundQuack::getCurrentLoop(int channel)
{
	int current;
	getChannel(channel)->getLoopCount(&current);
	return current;
}

void SoundQuack::setVolume(int channel, float volume)
{
	getChannel(channel)->setVolume(volume);
}

float SoundQuack::getVolume(int channel)
{
	float volume;
	getChannel(channel)->getVolume(&volume);
	return volume;
}


FMOD::Channel* SoundQuack::getChannel(int index)
{
	FMOD::Channel* channelAux;
	FMOD::ChannelGroup* channel_group;
	systemFMOD_->getMasterChannelGroup(&channel_group);
	channel_group->getChannel(index, &channelAux);
	return channelAux;
}