#pragma once

#include <iostream>
#include <map>
#include <memory.h>
#include <list>
#include <fmod_dsp_effects.h>		// INEVITABLE: gcc no admite forward declaration de typedef enum (FMOD_DSP_TYPE)
#include <fmod_common.h>
#include <vector>



namespace FMOD {					// evitar incluir .h de FMOD
	class Sound;
	class System;
	class DSP;
	class Channel;
	typedef unsigned int FMOD_MODE;
}
struct FMOD_VECTOR;

class SoundQuack
{
private:

	static std::unique_ptr<SoundQuack> instance_;

	std::vector<bool> listeners_;

	std::map<FMOD::Sound*, FMOD::Channel*> channels_;

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

	void removeSound(FMOD::Sound* sound);

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

	void set3DTransform(FMOD::Sound* sound, FMOD_VECTOR soundPos, FMOD_VECTOR soundVel = { 0,0,0 });

	void update();

	void updateListener(int index, FMOD_VECTOR listenerPos, FMOD_VECTOR listenerFW, FMOD_VECTOR listenerUP, FMOD_VECTOR listenerVel = { 0,0,0 });

	int getNewListener();

	void removeListener(int index);
};