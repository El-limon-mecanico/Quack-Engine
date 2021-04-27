#include "Rigidbody.h"
#include "BulletQuack.h"
#include "QuackEntity.h"
#include "BtOgre.h"
#include "MeshRenderer.h"
#include "QuackEnginePro.h"

Rigidbody::Rigidbody(QuackEntity* e) : collisions(std::vector<CollisionInfo>())
{
}

Rigidbody::~Rigidbody()
{
}


bool Rigidbody::init(luabridge::LuaRef parameterTable)
{
	std::string type = readVariable<std::string>(parameterTable, "Type");
	int mass = readVariable<int>(parameterTable, "Mass");
	
	if (type == "Box") setRigidbody(mass, BtOgre::ColliderType::CT_BOX);
	else if (type == "Sphere")setRigidbody(mass, BtOgre::ColliderType::CT_SPHERE);
	else if (type == "Trimesh")setRigidbody(mass, BtOgre::ColliderType::CT_TRIMESH);
	else if (type == "Hull")setRigidbody(mass, BtOgre::ColliderType::CT_HULL);

	
	
	return true;
}


void Rigidbody::setRigidbody(int mass, BtOgre::ColliderType type)
{
	BtOgre::ColliderType t = (BtOgre::ColliderType)type;
 	Render* renderCmp = entity_->getComponent<Render>("Render");
	rb_ = BulletQuack::Instance()->getWorld()->addRigidBody(mass, renderCmp->getOgreEntity(), t); //TODO 
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


