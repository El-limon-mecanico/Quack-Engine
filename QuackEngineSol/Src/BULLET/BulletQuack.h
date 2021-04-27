#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

#include <memory>

namespace Ogre {
	class Root;
	class SceneNode;
	class Entity;
}

namespace BtOgre {
	class DynamicsWorld;
	class CollisionListener;
	enum ColliderType;
}

class btRigidBody;

class BulletQuack {
private:

	static std::unique_ptr<BulletQuack> instance_;

	BtOgre::DynamicsWorld* world_;

	void init();

public:

	static bool Init();

	static BulletQuack* Instance();

	BulletQuack() {
		init();
	}

	~BulletQuack() {}

	void stepPhysics(double deltaTime);

	btRigidBody* addRigidBody(Ogre::Entity* e, BtOgre::CollisionListener* listener, float mass = 1,  BtOgre::ColliderType col = (BtOgre::ColliderType)1);
};

#endif // !_PHYSICS_MANAGER_



