#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

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

class QUACK_ENGINE_PRO_API Rigidbody : public Component {
private:

	struct CollisionInfo {
		Rigidbody* rb = nullptr;
		float time = 0;
		Vector3D point;
		bool trigger;
	};

	btRigidBody* rb_ = nullptr;

	float mass_ = 1;

	ColliderType colType_ = CT_BOX;

	std::vector<CollisionInfo> collisions;

	static void sendContacts(void* first, void* other, const btManifoldPoint& manifoldPoint);

	void contact(Rigidbody* other, const btManifoldPoint& manifoldPoint);

	bool firstEnable_ = true;
	
	bool trigger_ = false;

	bool static_ = false;

	Vector3D positionConstrains_; 
	Vector3D rotationConstrains_;

public:

	Rigidbody();

	~Rigidbody();

	static std::string GetName() { return "Rigidbody"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void preUpdate() override;

	virtual void physicsUpdate() override;

	virtual void lateUpdate() override;

	virtual void onEnable() override;

	virtual void onDisable() override;

	void setRigidbody(int mass, ColliderType type, bool trigger_ = false, bool statc = false);

	void setTrigger(bool trigger);

	btRigidBody* getRigidbody() { return rb_; }

	void setMass(float mass);

	void setStatic(bool statc);

	void resetTransform();

	float getMass();

	void addForce(Vector3D force, ForceMode mode = FORCE);

	void addTorque(Vector3D force, ForceMode mode = FORCE);

	void clearForce();

	void setGravity(Vector3D gravity);

	void setStatic();

	bool isStatic();

	Vector3D velocity();

	void setVelocity(Vector3D v);

	Vector3D angularVelocity();

	void setAngularVelocity(Vector3D v);

	void setRotationConstrains(bool x , bool y, bool z);

	void setPositionConstrains(bool x, bool y, bool z);

	void removeCollisionData(Rigidbody* rb);

	Vector3D positionConstrains() { return positionConstrains_; }
	Vector3D rotationConstrains() { return rotationConstrains_; }
};