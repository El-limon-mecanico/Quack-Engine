#pragma once
#include "Component.h"

//no se si esto es lo correcto para acceder a las clases que necesito?¿?¿?¿
namespace Ogre {
	class Root;
	class SceneManager;
}

namespace BtOgre {
	class DynamicsWorld;
}

class btRigidBody;

enum ColliderType
{
	CT_BOX,
	CT_SPHERE,
	CT_TRIMESH,
	CT_HULL
};


class Rigidbody : public Component {
private:
	btRigidBody* rb_;
public:
	Rigidbody(QuackEntity* e = nullptr);
	~Rigidbody();

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setRigidbody(int mass = 1, ColliderType type = CT_BOX);
	
	btRigidBody* getRigidbody() { return rb_; }
	
};