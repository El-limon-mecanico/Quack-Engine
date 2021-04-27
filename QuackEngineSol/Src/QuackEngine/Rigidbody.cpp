#include "Rigidbody.h"
#include "BulletQuack.h"
#include "QuackEntity.h"
#include "BtOgre.h"
#include "QuackEnginePro.h"

Rigidbody::Rigidbody(QuackEntity* e) : collisions(std::vector<CollisionInfo>())
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

void Rigidbody::preUpdate()
{
	for (CollisionInfo& obj : collisions)
		obj.time += QuackEnginePro::Instance()->time()->deltaTime();
}

void Rigidbody::lateUpdate()
{
	for (auto it = collisions.begin(); it != collisions.end();) {
		if ((*it).time > TIME_TO_EXIT) {
			entity_->onCollisionExit((*it).other);
			it = collisions.erase(it);
		}
		else
			it++;
	}
}

void Rigidbody::setRigidbody(int mass, BtOgre::ColliderType type)
{
	rb_ = BulletQuack::Instance()->addRigidBody(entity_->getOgreEntity(), this, mass, type);
}

void Rigidbody::contact(BtOgre::CollisionListener* other, const btManifoldPoint& manifoldPoint)
{
	QuackEntity* e = static_cast<Rigidbody*>(other)->entity_;

	for (CollisionInfo& obj : collisions) {
		if (obj.other == e) {
			obj.time = 0;
			entity_->onCollisionStay(e);
			return;
		}
	}
	collisions.push_back({ e,0 });
	entity_->onCollisionEnter(e);
}


