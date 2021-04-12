#ifndef _QUACK_ENGINE_PRO_
#define _QUACK_ENGINE_PRO_


class QuackFrameListener;
class PhysicsManager;

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
}

class QuackEnginePro {

protected:

private:

	Ogre::Root* root_;

	Ogre::RenderWindow* window_;

	Ogre::SceneManager* mSM_;

	QuackFrameListener* frameListener_;

	PhysicsManager* physicsManager_;

public:


};

#endif // !_QUACK_ENGINE_PRO_

