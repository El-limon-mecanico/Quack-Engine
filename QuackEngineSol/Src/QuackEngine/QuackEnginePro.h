#ifndef _QUACK_ENGINE_PRO_
#define _QUACK_ENGINE_PRO_

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include "QuackTime.h"
#include <memory>
#include <string>

class BulletQuack;
class fmod_quack;
class OgreQuack;
class SDL_Window;
class CEGUIQuack;
class ResourceMng;
class InputManager;

const int NFrames = 50;
const float FIXED_TIME_UPDATE = 1.0f/NFrames;

class QUACK_ENGINE_PRO_API QuackEnginePro {
private:

	static std::unique_ptr<QuackEnginePro> instance_;
	
	std::string assets_route = "";

	SDL_Window* sdlWindow_;

	QuackTime* quackTime_;

	fmod_quack* fmod_quack_;

	CEGUIQuack* cegui_;

	void pollEvents();

	void setup();

	void update();

	bool updateStarted = false;

	bool exit = true;

	void prueba();

	float fixedTime = 0;
	
	static void pruebaBotonCallback();

	void readAssetsRoute();

public:

	QuackEnginePro() {
		setup();
	}

	~QuackEnginePro();

	static bool Init();

	static QuackEnginePro* Instance();

	fmod_quack* getFmodQuack();

	void start();

	QuackTime* time();

};

#endif // !_QUACK_ENGINE_PRO_

