#pragma once

#include <iostream>
#include <map>
#include <memory.h>
#include <list>
#include <fmod_dsp_effects.h>		// INEVITABLE: gcc no admite forward declaration de typedef enum (FMOD_DSP_TYPE)

namespace FMOD {					// evitar incluir .h de FMOD
	class Sound;
	class System;
	class DSP;
	class Channel;
	typedef unsigned int FMOD_MODE;
}

class SoundQuack
{
private:

	static std::unique_ptr<SoundQuack> instance_;

	int currentChannel = 0;

	std::list <FMOD::Sound*> sounds_;
	//std::map<std::string, FMOD::Sound*> sounds_;
	std::map<std::string, FMOD::DSP*> dsp_;
	FMOD::System* systemFMOD_ = NULL;

	std::string assetsRouteFmod = "";

	FMOD::Channel* getChannel(FMOD::Sound* sound);
	
	SoundQuack(std::string route);

public:

	// devuelve puntero al singleton
	static SoundQuack* Instance();

	~SoundQuack();
	
	static SoundQuack* Init(std::string route);
	
	FMOD::Sound* createSound(std::string sound, int flags = 0);
	void create3DSound(std::string sound);

	void removeSound(FMOD::Sound* sound );

	void playSound(FMOD::Sound* sound, float volume);
	void pauseSound(FMOD::Sound* sound, bool pause);
	bool isPlaying(FMOD::Sound* sound);
	void setVolume(FMOD::Sound* sound, float value);
	float getVolume(FMOD::Sound* sound);
	void stopSound(FMOD::Sound* sound);
	void loop(FMOD::Sound* sound, int times);
	int getCurrentLoop(FMOD::Sound* sound);
	void setMode(FMOD::Sound* sound, int flags);
	FMOD::FMOD_MODE getMode(FMOD::Sound* sound);

	int createDSP(FMOD_DSP_TYPE type, std::string id);
	void addDSP(FMOD::Sound* sound, std::string isDSP);

	void soundLoop(std::string& id);
};