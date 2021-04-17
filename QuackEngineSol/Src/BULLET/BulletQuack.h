#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

#include <memory>

namespace Ogre {
	class Root;
	class SceneManager;
}

namespace BtOgre {
	class DynamicsWorld;
}

class BulletQuack {
private:

	static std::unique_ptr<BulletQuack> instance_;

	Ogre::Root* root_;

	Ogre::SceneManager* mSM_;

	BtOgre::DynamicsWorld* world_;

	void init();

	void pruebas();

public:

	static bool Init(Ogre::Root* root, Ogre::SceneManager* msM);

	static BulletQuack* Instance();


	BulletQuack(Ogre::Root* root, Ogre::SceneManager* msM) :root_(root), mSM_(msM) {
		init();
	}

	~BulletQuack() {}

	void addSceneManager(Ogre::SceneManager* mngr) { mSM_ = mngr; }

	void stepPhysics(double deltaTime);
};

#endif // !_PHYSICS_MANAGER_



