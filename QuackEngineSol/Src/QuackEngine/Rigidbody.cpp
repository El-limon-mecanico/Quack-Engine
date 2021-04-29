#include "Rigidbody.h"
#include "BulletQuack.h"
#include "QuackEntity.h"
#include "BtOgre.h"
#include "MeshRenderer.h"
#include "QuackEnginePro.h"


void Rigidbody::sendContacts(void* first, void* other, const btManifoldPoint& manifoldPoint)
{
	static_cast<Rigidbody*>(first)->contact(static_cast<Rigidbody*>(other), manifoldPoint);
}

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
	MeshRenderer* renderCmp = entity_->getComponent<MeshRenderer>();
	if (!renderCmp)
		renderCmp = entity_->addComponent<MeshRenderer>();
	rb_ = BulletQuack::Instance()->addRigidBody(mass, renderCmp->getOgreEntity(), type, &sendContacts, this);
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
			entity_->onCollisionExit((*it).rb->entity_);
			it = collisions.erase(it);
		}
		else
			it++;
	}
}


void Rigidbody::contact(Rigidbody* other, const btManifoldPoint& manifoldPoint)
{
	btVector3 v = manifoldPoint.getPositionWorldOnA();

	for (CollisionInfo& obj : collisions) {
		if (obj.rb == other) {
			obj.time = 0;
			obj.point = Vector3D((float)v.x(), (float)v.y(), (float)v.z());
			entity_->onCollisionStay(other->entity_);
			return;
		}
	}
	collisions.push_back({ other,0 ,Vector3D((float)v.x(),(float)v.y() ,(float)v.z()) });
	entity_->onCollisionEnter(other->entity_);
}
