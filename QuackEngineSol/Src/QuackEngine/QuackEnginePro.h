#ifndef _QUACK_ENGINE_PRO_
#define _QUACK_ENGINE_PRO_

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif


class QuackTime;
class BulletQuack;
class fmod_quack;
class OgreQuack;
class SDL_Window;

class QUACK_ENGINE_PRO_API QuackEnginePro {
private:

	static std::unique_ptr<QuackEnginePro> instance_;

	SDL_Window* sdlWindow_;

	QuackTime* quackTime_;

	fmod_quack* fmod_quack_;

	void pollEvents();

	void setup();

	void update();

	bool updateStarted = false;

	bool exit = true;

public:

	QuackEnginePro() {
		setup();
	}

	~QuackEnginePro() {}

	static bool Init();

	static QuackEnginePro* Instance();

	fmod_quack* getFmodQuack();

	void start();

	QuackTime* time();

};

#endif // !_QUACK_ENGINE_PRO_

