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

class btCollisionConfiguration;
class btCollisionDispatcher;
class btConstraintSolver;
class btBroadphaseInterface;
class btDynamicsWorld;
class btRigidBody;

class BulletQuack {
private:

	static std::unique_ptr<BulletQuack> instance_;

	/*std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
	std::unique_ptr<btCollisionDispatcher> mDispatcher;
	std::unique_ptr<btConstraintSolver> mSolver;
	std::unique_ptr<btBroadphaseInterface> mBroadphase;
	btDynamicsWorld* mBtWorld;*/

	BtOgre::DynamicsWorld* world_;

	void init();

	//static void onTick(btDynamicsWorld* world, float timeStep);

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



