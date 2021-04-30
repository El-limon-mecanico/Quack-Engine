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
	//TODO: control de errores si no carga una variable
	std::string type = readVariable<std::string>(parameterTable, "Type");
	int mass = readVariable<int>(parameterTable, "Mass");

	if (type == "Box") setRigidbody(mass, ColliderType::CT_BOX);
	else if (type == "Sphere")setRigidbody(mass, ColliderType::CT_SPHERE);
	else if (type == "Trimesh")setRigidbody(mass, ColliderType::CT_TRIMESH);
	else if (type == "Hull")setRigidbody(mass, ColliderType::CT_HULL);


	return true;
}

void Rigidbody::setRigidbody(int mass, ColliderType type)
{
	BtOgre::ColliderType t = (BtOgre::ColliderType)type;
	MeshRenderer* renderCmp = entity_->getComponent<MeshRenderer>();
	if (!renderCmp)
		renderCmp = entity_->addComponent<MeshRenderer>();
	rb_ = BulletQuack::Instance()->addRigidBody(mass, renderCmp->getOgreEntity(), t, &sendContacts, this);
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
			entity_->onCollisionExit((*it).rb->entity_, (*it).point);
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
			entity_->onCollisionStay(other->entity_, obj.point);
			return;
		}
	}
	Vector3D p = Vector3D((float)v.x(), (float)v.y(), (float)v.z());
	collisions.push_back({ other,0 , p });
	entity_->onCollisionEnter(other->entity_, p);
}

void Rigidbody::setMass(float mass)
{
	BulletQuack::Instance()->changeMass(mass, rb_);
}

float Rigidbody::getMass()
{
	return rb_->getMass();
}

void Rigidbody::addForce(Vector3D force, ForceMode mode, bool local)
{
	force = force.toOgre();
	btVector3 f = btVector3(force.x(), force.y(), force.z());

	if (mode)
		rb_->applyCentralImpulse(f);
	else
		rb_->applyCentralForce(f);
}

void Rigidbody::addTorque(Vector3D force, ForceMode mode, bool local)
{
	force = force.toOgre();
	btVector3 f = btVector3(force.x(), force.y(), force.z());

	if (mode)
		rb_->applyTorque(f);
	else
		rb_->applyTorqueImpulse(f);
}


void Rigidbody::clearForce()
{
	rb_->clearForces();
}

void Rigidbody::setGravity(Vector3D gravity)
{
	gravity = gravity.toOgre();
	btVector3 f = btVector3(gravity.x(), gravity.y(), gravity.z());
	rb_->setGravity(f);
}

void Rigidbody::setStatic()
{
	setMass(0);
}

bool Rigidbody::isStatic()
{
	return getMass() == 0;
}


