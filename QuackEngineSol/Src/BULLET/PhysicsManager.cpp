#include "PhysicsManager.h"

void PhysicsManager::init() {

	// mSM_ = root_->getSceneManager("nombre");		// NECESITAMOS SABER EL SCENE MANAGER

	world_ = new DynamicsWorld(Ogre::Vector3(0, -5, 0));
}

void PhysicsManager::stepPhysics(double deltaTime)
{
	world_->getBtWorld()->stepSimulation(deltaTime);
}
