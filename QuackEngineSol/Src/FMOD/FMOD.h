#pragma once
#include <iostream>
#include <map>
#include <fmod.hpp>

class Fmod
{
public:
	Fmod();

	void playSound(int channel, std::string id);
	void createSound(std::string sound, std::string id);
	void setVolume(int channel, float volume);
	
	void createDSP(FMOD_DSP_TYPE type, std::string id);
	void addDSP(int channel, std::string isDSP);
private:
	FMOD::System* systemFMOD_ = NULL;

	std::map<std::string, FMOD::Sound*> sounds_;
	std::map<std::string, FMOD::Sound*> dsp_;


	void FMOD_Init();

};
