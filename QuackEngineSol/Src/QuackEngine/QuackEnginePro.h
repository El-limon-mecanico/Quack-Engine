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

class QUACK_ENGINE_PRO_API QuackEnginePro {
private:

	static std::unique_ptr<QuackEnginePro> instance_;

	std::string assets_route = "";

	std::string windowName;

	SDL_Window* sdlWindow_;

	QuackTime* quackTime_;

	void pollEvents();

	void setup();

	void update();

	bool updateStarted = false;

	bool exit = true;

	void readAssetsRoute();

public:

	QuackEnginePro(std::string name) : windowName(name) {
		setup();
	}

	~QuackEnginePro();

	static bool Init(std::string name = "PONLE UN NOMBRE A LA VENTANA EN EL INIT");

	static QuackEnginePro* Instance();

	void start(std::string route, std::string name);

	QuackTime* time();

	void quit() { exit = true; }

	void setFullScreen(bool set);

	void setWindowSize(int width, int height);

	int getWindoWidth();

	int getWindoHeight();
};

#endif // !_QUACK_ENGINE_PRO_

