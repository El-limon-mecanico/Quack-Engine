#pragma once
#include "Component.h"
#include "BtOgre.h"

//no se si esto es lo correcto para acceder a las clases que necesito?¿?¿?¿


class Rigidbody : public Component, public BtOgre::CollisionListener {
private:

	btRigidBody* rb_;

public:

	std::string nombre = "name";

	Rigidbody(QuackEntity* e = nullptr);

	~Rigidbody();

	void setNombre(std::string nomb) { nombre = nomb; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setRigidbody(int mass = 1, BtOgre::ColliderType type = BtOgre::ColliderType::CT_BOX);
	
	btRigidBody* getRigidbody() { return rb_; }

	//virtual void contact(Ogre::MovableObject* other, const btManifoldPoint& manifoldPoint){}

	virtual void contact( CollisionListener* other, const btManifoldPoint& manifoldPoint);
	
};