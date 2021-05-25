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
class QUACK_ENGINE_PRO_API AudioListener : 
	public Component
{
private:
	SoundQuack* mngr_;
	int index_ = -1;
public:
	AudioListener();
	~AudioListener();

	static std::string GetName() { return "AudioListener"; }
	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) { return true; }
	
	virtual void preUpdate();
	virtual void onEnable();
	virtual void onDisable();
};