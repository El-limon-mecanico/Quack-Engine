#pragma once
#include <iostream>
#include <fmod_errors.h>
#include <fmod.hpp>
#include <map>
#include <memory.h>

class fmod_quack
{
private:

	static std::unique_ptr<fmod_quack> instance_;

	std::map<std::string, FMOD::Sound*> sounds_;
	std::map<std::string, FMOD::DSP*> dsp_;
	FMOD::System* systemFMOD_ = NULL;

	std::string assetsRouteFmod = "";

	static FMOD::Channel* GetChannel(int channel);
	
	fmod_quack(std::string route);

public:
	// devuelve puntero al singleton
	static fmod_quack* Instance();
	
	~fmod_quack();
	
	static fmod_quack* Init(std::string route);
	
	static void PlaySound(int channel, std::string id, float volume);
	static void CreateSound(std::string sound, std::string id);

	static void CreateDSP(FMOD_DSP_TYPE type, std::string id);
	static void AddDSP(int channel, std::string isDSP);

	static void PauseChannel(int channel, bool pause);
	static void StopChannel(int channel);
};

