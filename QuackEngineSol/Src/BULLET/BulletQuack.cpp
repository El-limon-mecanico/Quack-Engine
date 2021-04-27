#include "BulletQuack.h"
#include "BtOgre.h"
#include <assert.h>

using namespace BtOgre;

std::unique_ptr<BulletQuack>  BulletQuack::instance_;

//TODO AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
bool BulletQuack::Init(Ogre::Root* root, Ogre::SceneManager* msM) {
	assert(instance_.get() == nullptr);
	instance_.reset(new BulletQuack(root, msM));
	return instance_.get();
}

BulletQuack* BulletQuack::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}


void BulletQuack::init() {

	world_ = new DynamicsWorld(Ogre::Vector3(0, -100, 0));
}


void BulletQuack::stepPhysics(double deltaTime)
{
	world_->getBtWorld()->stepSimulation(deltaTime);
}
