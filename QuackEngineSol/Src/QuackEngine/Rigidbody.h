#pragma once
#include "Component.h"
#include "Vector3D.h"
//no se si esto es lo correcto para acceder a las clases que necesito?�?�?�

const float TIME_TO_EXIT = 0.1f;


namespace BtOgre {
	class DynamicsWorld;
	class CollisionListener;
	enum ColliderType;
}

class btManifoldPoint;
class btRigidBody;

class Rigidbody : public Component{
private:

	struct CollisionInfo {
		Rigidbody* rb = nullptr;
		float time = 0;
		Vector3D point;
	};

	btRigidBody* rb_ = nullptr;

	std::vector<CollisionInfo> collisions;
	
	static void sendContacts(void* first, void* other, const btManifoldPoint& manifoldPoint);
	
	void contact(Rigidbody* other, const btManifoldPoint& manifoldPoint);

public:

	Rigidbody(QuackEntity* e = nullptr);

	~Rigidbody();

	static std::string GetName() { return "Rigidbody"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void preUpdate() override;

	virtual void lateUpdate() override;

	void setRigidbody(int mass, BtOgre::ColliderType type);
	
	btRigidBody* getRigidbody() { return rb_; }
};