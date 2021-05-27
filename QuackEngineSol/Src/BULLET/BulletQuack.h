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
class btManifoldPoint;

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

	void stepPhysics(double deltaTime, float fixedTimeStep = 0.02);

	void changeMass(float mass, btRigidBody* rb);

	btRigidBody* addRigidBody(float mass, const Ogre::Entity* ent, BtOgre::ColliderType ct, void(*p)(void* , void*, const btManifoldPoint& mnf), void* listener);

	void addRigidBody(btRigidBody* rb);

	void removeRigidBody(btRigidBody* rb);

	BtOgre::DynamicsWorld* const getWorld() const { return world_; }
};

#endif // !_PHYSICS_MANAGER_