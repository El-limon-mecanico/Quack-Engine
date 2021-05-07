#include "BulletQuack.h"
#include "BtOgre.h"
#include <assert.h>

using namespace BtOgre;

std::unique_ptr<BulletQuack>  BulletQuack::instance_;


// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
bool BulletQuack::Init() {
	assert(instance_.get() == nullptr);
	instance_.reset(new BulletQuack());
	return instance_.get();
}

BulletQuack* BulletQuack::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}


void BulletQuack::init() {

	world_ = new DynamicsWorld(Ogre::Vector3(0, -980, 0));
}


void BulletQuack::stepPhysics(double deltaTime, float fixedTimeStep)
{
	world_->getBtWorld()->stepSimulation(deltaTime, 1, fixedTimeStep);
	//mBtWorld->stepSimulation(deltaTime);
}

void BulletQuack::changeMass(float mass, btRigidBody* rb)
{
	world_->getBtWorld()->removeRigidBody(rb);

	btVector3 inertia;
	rb->getCollisionShape()->calculateLocalInertia(mass, inertia);
	rb->setMassProps(mass, inertia);

	//Add the rigid body to the dynamics world
	world_->getBtWorld()->addRigidBody(rb);
}

btRigidBody* BulletQuack::addRigidBody(float mass, const Ogre::Entity* ent, BtOgre::ColliderType ct, void(*p)(void*, void*, const btManifoldPoint& mnf), void* listener)
{
	return world_->addRigidBody(mass, ent, ct, p, listener);
}

void BulletQuack::addRigidBody(btRigidBody* rb)
{
	world_->getBtWorld()->removeRigidBody(rb);
}

void BulletQuack::removeRigidBody(btRigidBody* rb)
{
	world_->getBtWorld()->addRigidBody(rb);
}
