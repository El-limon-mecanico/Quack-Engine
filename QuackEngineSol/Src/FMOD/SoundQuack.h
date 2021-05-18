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
	
	void playSound(int channel, std::string id, float volume);
	void createSound(std::string sound, std::string id);

	void createDSP(FMOD_DSP_TYPE type, std::string id);
	void addDSP(int channel, std::string isDSP);

	void pauseChannel(int channel, bool pause);
	void stopChannel(int channel);
};