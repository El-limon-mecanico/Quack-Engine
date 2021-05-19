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

Rigidbody::Rigidbody() : collisions(std::vector<CollisionInfo>())
{
}

Rigidbody::~Rigidbody()
{
	BulletQuack::Instance()->removeRigidBody(rb_);
	for (CollisionInfo i : collisions)
		i.rb->removeCollisionData(this);
	rb_ = nullptr;
}


bool Rigidbody::init(luabridge::LuaRef parameterTable)
{
	//TODO: control de errores si no carga una variable
	std::string type = readVariable<std::string>(parameterTable, "Type");
	mass_ = readVariable<int>(parameterTable, "Mass");
	trigger_ = readVariable<bool>(parameterTable, "Trigger");
	static_ = readVariable<bool>(parameterTable, "Static");
	LuaRef posCons = readVariable<LuaRef>(parameterTable, "PositionConstrains");
	LuaRef rotCons = readVariable<LuaRef>(parameterTable, "RotationConstrains");
	positionConstrains_ = Vector3D(posCons[1], posCons[2], posCons[3]);
	rotationConstrains_ = Vector3D(rotCons[1], rotCons[2], rotCons[3]);

	if (type == "Box") colType_ = CT_BOX;
	else if (type == "Sphere")colType_ = CT_SPHERE;
	else if (type == "Trimesh")colType_ = CT_TRIMESH;
	else if (type == "Hull")colType_ = CT_HULL;

	return true;
}

void Rigidbody::setRigidbody(int mass, ColliderType type, bool trigger, bool statc)
{
	BtOgre::ColliderType t = (BtOgre::ColliderType)type;
	MeshRenderer* renderCmp = entity_->getComponent<MeshRenderer>();
	if (!renderCmp)
		renderCmp = entity_->addComponent<MeshRenderer>();
	rb_ = BulletQuack::Instance()->addRigidBody(mass, renderCmp->getOgreEntity(), t, &sendContacts, this);

	setTrigger(trigger);

	if (statc)
		setStatic(true);
}

void Rigidbody::setTrigger(bool trigger)
{
	trigger_ = trigger;

	if (trigger)
		rb_->setCollisionFlags(DISABLE_DEACTIVATION);
	else
		rb_->setCollisionFlags(0);
}

void Rigidbody::preUpdate()
{
	for (CollisionInfo& obj : collisions)
		obj.time += QuackEnginePro::Instance()->time()->deltaTime();
}

void Rigidbody::physicsUpdate()
{
	transform->physicsUpdateTr();
}

void Rigidbody::lateUpdate()
{
	for (auto it = collisions.begin(); it != collisions.end();) {
		if ((*it).time > TIME_TO_EXIT) {
			if ((*it).rb)
				((*it).trigger) ? entity_->onTriggerExit((*it).rb->entity_, (*it).point) : entity_->onCollisionExit((*it).rb->entity_, (*it).point);
			it = collisions.erase(it);
		}
		else
			it++;
	}
}

void Rigidbody::onEnable()
{
	if (firstEnable_) {
		setRigidbody(mass_, colType_, trigger_, static_);
		setPositionConstrains(positionConstrains_.x, positionConstrains_.y, positionConstrains_.z);
		setRotationConstrains(rotationConstrains_.x, rotationConstrains_.y, rotationConstrains_.z);
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
			(other->trigger_ || trigger_) ? entity_->onTriggerStay(other->entity_, obj.point) : entity_->onCollisionStay(other->entity_, obj.point);
			return;
		}
	}
	Vector3D p = Vector3D((float)v.x(), (float)v.y(), (float)v.z());
	collisions.push_back({ other,0 , p , other->trigger_ || trigger_ });
	(other->trigger_ || trigger_) ? entity_->onTriggerEnter(other->entity_, p) : entity_->onCollisionEnter(other->entity_, p);
}

void Rigidbody::setMass(float mass)
{
	mass_ = mass_;
	BulletQuack::Instance()->changeMass(mass, rb_);
}

void Rigidbody::setStatic(bool statc)
{
	if (statc)
		BulletQuack::Instance()->changeMass(0, rb_);
	else
		setMass(mass_);

}

void Rigidbody::resetTransform()
{
	btTransform tr = rb_->getCenterOfMassTransform();
	tr.setOrigin(transform->position().toBulletPosition());
	tr.setRotation(transform->rotation().toBulletRotation());

	rb_->setWorldTransform(tr);
	rb_->getCollisionShape()->setLocalScaling(Vector3D::toBullet(transform->localScale()));
	rb_->getMotionState()->setWorldTransform(tr);
}

float Rigidbody::getMass()
{
	return rb_->getMass();
}

void Rigidbody::addForce(Vector3D force, ForceMode mode)
{
	if (mode)
		rb_->applyCentralImpulse(force.toBulletPosition());
	else
		rb_->applyCentralForce(force.toBulletPosition());
}

void Rigidbody::addTorque(Vector3D force, ForceMode mode)
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

Vector3D Rigidbody::velocity()
{
	return Vector3D::fromBulletPosition(rb_->getLinearVelocity());
}

void Rigidbody::setVelocity(Vector3D v)
{
	rb_->setLinearVelocity(v.toBulletPosition());
}

void Rigidbody::setPositionConstrains(bool x, bool y, bool z)
{
	positionConstrains_ = Vector3D(x, y, z);
	rb_->setLinearFactor(btVector3(!(int)x, !(int)y, !(int)z));
}

void Rigidbody::removeCollisionData(Rigidbody* rb)
{
	for (auto it = collisions.begin(); it != collisions.end();) {
		if ((*it).rb == rb) {
			((*it).trigger) ? entity_->onTriggerExit((*it).rb->entity_, (*it).point) : entity_->onCollisionExit((*it).rb->entity_, (*it).point);
			it = collisions.erase(it);
			return;
		}
		else
			it++;
	}
}


void Rigidbody::setRotationConstrains(bool x, bool y, bool z)
{
	rotationConstrains_ = Vector3D(x, y, z);
	rb_->setAngularFactor(btVector3(!(int)x, !(int)y, !(int)z));
}