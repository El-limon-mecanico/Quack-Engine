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
	mass_ = readVariable<int>(parameterTable, "Mass");

	if (type == "Box") colType_ = CT_BOX;
	else if (type == "Sphere")colType_ = CT_SPHERE;
	else if (type == "Trimesh")colType_ = CT_TRIMESH;
	else if (type == "Hull")colType_ = CT_HULL;


	return true;
}

void Rigidbody::setRigidbody(int mass, ColliderType type)
{
	BtOgre::ColliderType t = (BtOgre::ColliderType)type;
	MeshRenderer* renderCmp = entity_->getComponent<MeshRenderer>();
	if (!renderCmp)
		renderCmp = entity_->addComponent<MeshRenderer>();
	rb_ = BulletQuack::Instance()->addRigidBody(mass, renderCmp->getOgreEntity(), t, &sendContacts, this);
	rb_->setCollisionFlags(DISABLE_DEACTIVATION);
}

void Rigidbody::preUpdate()
{
	resetTransform();

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

void Rigidbody::onEnable()
{
	if (firsEnable_) {
		setRigidbody(mass_, colType_);
	}
	else {
		BulletQuack::Instance()->addRigidBody(rb_);
	}
}

void Rigidbody::onDisable()
{
	BulletQuack::Instance()->removeRigidBody(rb_);
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

void Rigidbody::resetTransform()
{
	btTransform tr = rb_->getCenterOfMassTransform();
	tr.setOrigin(transform->globalPosition().toBulletPosition());
	tr.setRotation(transform->rotation().toBulletRotation());

	rb_->setWorldTransform(tr);
	rb_->getMotionState()->setWorldTransform(tr);
}

float Rigidbody::getMass()
{
	return rb_->getMass();
}

void Rigidbody::addForce(Vector3D force, ForceMode mode, bool local)
{
	if (mode)
		rb_->applyCentralImpulse(force.toBulletPosition());
	else
		rb_->applyCentralForce(force.toBulletPosition());
}

void Rigidbody::addTorque(Vector3D force, ForceMode mode, bool local)
{
	if (mode)
		rb_->applyTorque(force.toBulletPosition());
	else
		rb_->applyTorqueImpulse(force.toBulletPosition());
}


void Rigidbody::clearForce()
{

	rb_->clearForces();
	btVector3 v(0, 0, 0);
	rb_->setLinearVelocity(v);
	rb_->setAngularVelocity(v);
}

void Rigidbody::setGravity(Vector3D gravity)
{
	rb_->setGravity(gravity.toBulletPosition());
}

void Rigidbody::setStatic()
{
	setMass(0);
}

bool Rigidbody::isStatic()
{
	return getMass() == 0;
}


