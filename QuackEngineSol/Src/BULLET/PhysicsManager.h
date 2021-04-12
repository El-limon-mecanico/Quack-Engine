#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

#include "BtOgre.h"

using namespace BtOgre;

class PhysicsManager {
private:

	Ogre::Root* root_;

	Ogre::SceneManager* mSM_;

	DynamicsWorld* world_;

	void init();

public:

	PhysicsManager(Ogre::Root* root) :root_(root) {
		init();
	}

	~PhysicsManager() {}

	void addSceneManager(Ogre::SceneManager* mngr) { mSM_ = mngr; }

	void stepPhysics(double deltaTime);
};

#endif // !_PHYSICS_MANAGER_



