//Componente encargada de producir sonido
#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include "Component.h"

class SoundQuack;

namespace FMOD {
	class Sound;
}

class QUACK_ENGINE_PRO_API AudioSource :
	public Component
{
private:

	SoundQuack* mngr_ = nullptr;
	FMOD::Sound* sound_;
	bool playing_ = false;
	bool D3_ = false;

	// Lua parameters
	float volume_=0;
	std::string source_="";

public:
	AudioSource();
	virtual ~AudioSource();
	
	static std::string GetName() { return "AudioSource"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void preUpdate();

	virtual void onEnable();

	virtual void onDisable();

	void play();
	void stop();
	void pause();
	void resume();
	bool isPlaying();
	void loop(int times = -1);
	int getCurrentLoop();
	void setVolume(float value);
	float getVolume();
};