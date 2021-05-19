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

class QUACK_ENGINE_PRO_API AudioSource3D :
	public Component
{
private:

	SoundQuack* mngr_ = nullptr;
	int channel = -1;		// almacena el canal en el que se esta reproduciendo el sonido
	
	float volume;
	std::string source;

public:
	AudioSource3D();
	virtual ~AudioSource3D();
	
	static std::string GetName() { return "AudioSource"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	void play();
	void stop();
	void pause();
	void resume();
	bool isPlaying();
	void setVolume(float value);
	float getVolume();
};