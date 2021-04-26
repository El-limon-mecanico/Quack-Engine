#include "Rigidbody.h"
#include "BulletQuack.h"
#include "QuackEntity.h"

Rigidbody::Rigidbody(QuackEntity* e)
{
}

Rigidbody::~Rigidbody()
{
}

bool Rigidbody::init(luabridge::LuaRef parameterTable)
{
	if (parameterTable.state())
		enableExceptions(parameterTable);
	return true;
}

void Rigidbody::setRigidbody(int mass, BtOgre::ColliderType type)
{
	rb_ = BulletQuack::Instance()->addRigidBody(entity_->getOgreEntity(), this, mass, type);
}

void Rigidbody::contact(BtOgre::CollisionListener* other, const btManifoldPoint& manifoldPoint)
{
	Rigidbody* otherObj = static_cast<Rigidbody*>(other);

	std::cout << "Yo " << nombre << " me he chocado con " << otherObj->nombre << "\n\n";
}


