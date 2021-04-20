#include "Rigidbody.h"
#include "BulletQuack.h"
#include "QuackEntity.h"
#include "BtOgre.h"

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

void Rigidbody::setRigidbody(int mass, ColliderType type)
{
	BtOgre::ColliderType t = (BtOgre::ColliderType)type;
	rb_ = BulletQuack::Instance()->getWorld()->addRigidBody(mass, entity_->getOgreEntity(), t);
}


