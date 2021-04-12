#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

namespace Ogre {
	class Root;
	class SceneManager;
}

namespace BtOgre {
	class DynamicsWorld;
}

class PhysicsManager {
private:

	Ogre::Root* root_;

	Ogre::SceneManager* mSM_;

	BtOgre::DynamicsWorld* world_;

	void init();

	void pruebas();

public:

	PhysicsManager(Ogre::Root* root, Ogre::SceneManager* msM) :root_(root), mSM_(msM) {
		init();
	}

	~PhysicsManager() {}

	void addSceneManager(Ogre::SceneManager* mngr) { mSM_ = mngr; }

	void stepPhysics(double deltaTime);
};

#endif // !_PHYSICS_MANAGER_



