#pragma once
#include "Component.h"

const float TIME_TO_EXIT = 0.1f;


enum ForceMode {
	FORCE,
	IMPULSE
};

namespace BtOgre {
	class DynamicsWorld;
	class CollisionListener;
}

enum ColliderType {
	CT_BOX,
	CT_SPHERE,
	CT_TRIMESH,
	CT_HULL
};

class btManifoldPoint;
class btRigidBody;

class Rigidbody : public Component {
private:

	struct CollisionInfo {
		Rigidbody* rb = nullptr;
		float time = 0;
		Vector3D point;
	};

	btRigidBody* rb_ = nullptr;

	float mass_ = 1;

	ColliderType colType_ = CT_BOX;

	std::vector<CollisionInfo> collisions;

	static void sendContacts(void* first, void* other, const btManifoldPoint& manifoldPoint);

	void contact(Rigidbody* other, const btManifoldPoint& manifoldPoint);

	bool firstEnable_ = true;
	
	bool trigger_ = false;

public:

	Rigidbody(QuackEntity* e = nullptr);

	~Rigidbody();

	static std::string GetName() { return "Rigidbody"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void preUpdate() override;

	virtual void physicsUpdate() override;

	virtual void lateUpdate() override;

	virtual void onEnable() override;

	virtual void onDisable() override;

	void setRigidbody(int mass, ColliderType type, bool trigger_ = false);

	void setTrigger(bool trigger);

	btRigidBody* getRigidbody() { return rb_; }

	void setMass(float mass);

	void resetTransform();

	float getMass();

	void addForce(Vector3D force, ForceMode mode = FORCE, bool local = false);

	void addTorque(Vector3D force, ForceMode mode = FORCE, bool local = false);

	void clearForce();

	void setGravity(Vector3D gravity);

	void setStatic();

	bool isStatic();
};