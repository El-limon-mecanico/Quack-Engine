#pragma once

#include <iostream>
#include <map>
#include <memory.h>
#include <fmod_dsp_effects.h>		// INEVITABLE: gcc no admite forward declaration de typedef enum (FMOD_DSP_TYPE)

namespace FMOD {					// evitar incluir .h de FMOD
	class Sound;
	class System;
	class DSP;
	class Channel;
}

class SoundQuack
{
private:

	static std::unique_ptr<SoundQuack> instance_;

	int currentChannel = 0;

	std::map<std::string, FMOD::Sound*> sounds_;
	std::map<std::string, FMOD::DSP*> dsp_;
	FMOD::System* systemFMOD_ = NULL;

	std::string assetsRouteFmod = "";

	FMOD::Channel* getChannel(int channel);
	
	SoundQuack(std::string route);

public:

	// devuelve puntero al singleton
	static SoundQuack* Instance();

	~SoundQuack();
	
	static SoundQuack* Init(std::string route);
	
	int createSound(std::string sound, std::string id);
	int create3DSound(std::string sound, std::string id, int flags);

	void playChannel(int channel, std::string id, float volume);
	void pauseChannel(int channel, bool pause);
	bool isPlaying(int channel);
	void setVolume(int channel, float value);
	float getVolume(int channel);
	void stopChannel(int channel);

	void createDSP(FMOD_DSP_TYPE type, std::string id);
	void addDSP(int channel, std::string isDSP);
};