#ifndef _QUACK_ENGINE_PRO_
#define _QUACK_ENGINE_PRO_

#include <memory>
#include <assert.h>

class QuackFrameListener;
class BulletQuack;
class fmod_quack;
class OgreQuack;
class SDL_Window;

class QuackEnginePro {
private:

	static std::unique_ptr<QuackEnginePro> instance_;

	SDL_Window* sdlWindow_;

	QuackFrameListener* frameListener_;

	BulletQuack* physicsManager_;

	OgreQuack* ogreQuack_;

	fmod_quack* fmod_quack_;

	void pollEvents();

public:

	QuackEnginePro() {}

	~QuackEnginePro() {}

	static QuackEnginePro* init() {
		assert(instance_.get() == nullptr);
		instance_.reset(new QuackEnginePro());
		return instance_.get();
	}

	static QuackEnginePro* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	OgreQuack* getOgreQuack() { return ogreQuack_; }

	BulletQuack* getPhysicsManager() { return physicsManager_; }

	fmod_quack* getFmodQuack() { return fmod_quack_; }

	void setup();

	void start();

	void update();


};

#endif // !_QUACK_ENGINE_PRO_

