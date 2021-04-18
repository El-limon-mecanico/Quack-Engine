#ifndef _QUACK_ENGINE_PRO_
#define _QUACK_ENGINE_PRO_

#include <memory>
#include <assert.h>

class QuackFrameListener;
class PhysicsManager;
class fmod_quack;
class OgreQuack;

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
	class SceneNode;
}

class QuackEnginePro {
private:

	static std::unique_ptr<QuackEnginePro> instance_;

	Ogre::Root* root_;

	Ogre::RenderWindow* window_;

	Ogre::SceneManager* mSM_;

	QuackFrameListener* frameListener_;

	PhysicsManager* physicsManager_;

	OgreQuack* ogreQuack_;

	fmod_quack* fmod_quack_;

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
	
	void setup();

	void start();

	void update();

	//MÉTODO PROVISIONAL: CON EL CAMBIO RECIENTE A SINGLETON, ESTO NO ES NECESARIO
	OgreQuack* getOgreQuack() { return ogreQuack_; }

};

#endif // !_QUACK_ENGINE_PRO_

