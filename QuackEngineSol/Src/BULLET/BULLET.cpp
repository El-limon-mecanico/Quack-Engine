#include "BULLET.h"
#include "BtOgre.h"
#include <iostream>

using namespace BtOgre;

void BULLET_Init() {

	Ogre::Root* root;
	root = new Ogre::Root();

	Ogre::RenderWindow* mWindow;

	root->showConfigDialog(NULL);

	mWindow = root->initialise(true, "DIOS SANTO LA VENTANA");

	Ogre::SceneManager* mSM;

	mSM = root->createSceneManager();

	Ogre::Camera* mCamera;

	mCamera = mSM->createCamera("MainCam");

	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(100000);
	mCamera->setAutoAspectRatio(true);


	Ogre::SceneNode* mNodeCamera = mSM->getRootSceneNode()->createChildSceneNode();
	mNodeCamera->attachObject(mCamera);

	mNodeCamera->setPosition(0, 0, 0);
	mNodeCamera->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(1, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	mSM->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	DynamicsWorld* _world = new DynamicsWorld(Ogre::Vector3(0, -5, 0));

	Ogre::Entity* e = mSM->createEntity(Ogre::SceneManager::PrefabType::PT_CUBE);

	Ogre::SceneNode* meNode = mSM->getRootSceneNode()->createChildSceneNode();

	meNode->attachObject(e);

	meNode->setPosition(0, 160, 0);
	btRigidBody* rb = _world->addRigidBody(1, e, BtOgre::ColliderType::CT_BOX);


	Ogre::Entity* plane = mSM->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);

	Ogre::SceneNode* mplaneNode = mSM->getRootSceneNode()->createChildSceneNode();

	mplaneNode->attachObject(plane);

	btRigidBody* planeRb = _world->addRigidBody(1, plane, BtOgre::ColliderType::CT_BOX);
	planeRb->setGravity(btVector3(0, 5, 0));


	while (true) {
		std::cout << "CUBO: yPos->" << rb->getCenterOfMassPosition().y() <<
			" rot: x->" << rb->getCenterOfMassTransform().getRotation().x() << " y->" << rb->getCenterOfMassTransform().getRotation().y()
			<< " z->" << rb->getCenterOfMassTransform().getRotation().z();
		std::cout << " --- " << "PLANO: yPos->" << planeRb->getCenterOfMassPosition().y() <<
			" rot: x->" << planeRb->getCenterOfMassTransform().getRotation().x() << " y->" << planeRb->getCenterOfMassTransform().getRotation().y()
			<< " z->" << planeRb->getCenterOfMassTransform().getRotation().z() << std::endl;
		_world->getBtWorld()->stepSimulation(0.0001);
		root->_fireFrameStarted();
		root->renderOneFrame();
		root->_fireFrameEnded();
	}

	//while (true)
	//{
	//	// OgreBites::WindowEventUtilities::messagePump();  WindowEventUtilities se ha mudado con el traidor OgreBites y no sabemos como sustituir esta linea

	//	if (mWindow->isClosed()) return;

	//	if (!root->renderOneFrame()) return;
	//}
}