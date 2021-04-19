#include "BulletQuack.h"
#include "BtOgre.h"
#include <assert.h>

using namespace BtOgre;

std::unique_ptr<BulletQuack>  BulletQuack::instance_;

// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
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

	pruebas();
}

void BulletQuack::pruebas()
{

	Ogre::Entity* e = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE);

	Ogre::SceneNode* mNode = mSM_->getRootSceneNode()->createChildSceneNode();

	mNode->attachObject(e);

	mNode->setPosition(0, 300, 0);

	btRigidBody* rb = world_->addRigidBody(1, e, BtOgre::ColliderType::CT_SPHERE);


	Ogre::Entity* e2 = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE);

	Ogre::SceneNode* mNode2 = mSM_->getRootSceneNode()->createChildSceneNode();

	mNode2->attachObject(e2);

	mNode2->setPosition(50, 500, 0);

	btRigidBody* rb2 = world_->addRigidBody(1, e2, BtOgre::ColliderType::CT_SPHERE);

	/*

	Ogre::Entity* e3 = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE);

	Ogre::SceneNode* mNode3 = mSM_->getRootSceneNode()->createChildSceneNode();

	mNode3->attachObject(e3);

	mNode3->setPosition(200, 700, 0);

	btRigidBody* rb3 = world_->addRigidBody(1, e3, BtOgre::ColliderType::CT_SPHERE);*/





	// PLANO

	Ogre::Entity* plane = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);

	Ogre::SceneNode* mplaneNode = mSM_->getRootSceneNode()->createChildSceneNode();

	mplaneNode->attachObject(plane);

	mplaneNode->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(Ogre::Degree(-90)));

	mplaneNode->scale(5, 5, 1);

	btRigidBody* planeRb = world_->addRigidBody(0, plane, BtOgre::ColliderType::CT_BOX);

	planeRb->setGravity(btVector3(0, 0, 0));
}

void BulletQuack::stepPhysics(double deltaTime)
{
	world_->getBtWorld()->stepSimulation(deltaTime);
}
