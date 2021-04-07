#pragma once
#include <iostream>
#include <fmod_errors.h>
#include <fmod.hpp>
#include <map>



class fmod_quack
{
private:
	std::map<std::string, FMOD::Sound*> sounds_;
	std::map<std::string, FMOD::DSP*> dsp_;
	FMOD::System* systemFMOD_ = NULL;

public:
	fmod_quack();
	~fmod_quack();
	
	void FMOD_Init();
	
	void playSound(int channel, std::string id, float volume);
	void createSound(std::string sound, std::string id);

	void createDSP(FMOD_DSP_TYPE type, std::string id);
	void addDSP(int channel, std::string isDSP);

	void pauseChannel(int channel, bool pause);
};

