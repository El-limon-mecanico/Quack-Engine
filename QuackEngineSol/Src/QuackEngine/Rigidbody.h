#pragma once
#include "Component.h"
#include "BtOgre.h"

//no se si esto es lo correcto para acceder a las clases que necesito?�?�?�

const float TIME_TO_EXIT = 0.1f;

class Rigidbody : public Component, public BtOgre::CollisionListener {
private:

	struct CollisionInfo {
		QuackEntity* other = 0;
		float time = 0;
	};

	btRigidBody* rb_ = nullptr;

	std::vector<CollisionInfo> collisions;

public:

	Rigidbody(QuackEntity* e = nullptr);

	~Rigidbody();

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void preUpdate() override;

	//virtual void update();

	virtual void lateUpdate() override;

	void setRigidbody(int mass = 1, BtOgre::ColliderType type = BtOgre::ColliderType::CT_BOX);
	
	btRigidBody* getRigidbody() { return rb_; }

	virtual void contact( CollisionListener* other, const btManifoldPoint& manifoldPoint);
	
};