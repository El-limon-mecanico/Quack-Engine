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


void BulletQuack::stepPhysics(double deltaTime)
{
	world_->getBtWorld()->stepSimulation(deltaTime);
	//mBtWorld->stepSimulation(deltaTime);
}

btRigidBody* BulletQuack::addRigidBody(Ogre::Entity* e, CollisionListener* listener, float mass, BtOgre::ColliderType col)
{

	return world_->addRigidBody(mass, e, col, listener);
}
