#include <iostream>
#include <OgreRoot.h>
#include <OgreEntity.h>
#include "OgreViewport.h"
#include "OgreRenderWindow.h"

void OGRE_Init()
{
	std::cout << "\n\n\nEMPIEZA LA INICIALIZACI�N DE OGRE\n\n";

	Ogre::Root* root;
	root = new Ogre::Root();

	Ogre::RenderWindow* mWindow;

	root->showConfigDialog(NULL);

	mWindow = root->initialise(true, "DIOS SANTO LA VENTANA");

	Ogre::SceneManager* mSceneMngr;

	mSceneMngr = root->createSceneManager();

	Ogre::Camera* mCamera;

	mCamera = mSceneMngr->createCamera("MainCam");

	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(100000);
	mCamera->setAutoAspectRatio(true);


	Ogre::SceneNode* mNodeCamera = mSceneMngr->getRootSceneNode()->createChildSceneNode();
	mNodeCamera->attachObject(mCamera);

	mNodeCamera->setPosition(0, 0, 0);
	mNodeCamera->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	mSceneMngr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));


	while (true)
	{
		// Ogre::WindowEventUtilities::messagePump();  WindowEventUtilities se ha mudado con el traidor OgreBites y no sabemos como sustituir esta linea

		if (mWindow->isClosed()) return;

		if (!root->renderOneFrame()) return;
	}
}

void prueba(fmod_quack* fmod_sound)
{
	fmod_sound->createSound(std::string("singing.wav"), "Cantando");
	fmod_sound->playSound(0, "Cantando", 1);
	fmod_sound->createDSP(FMOD_DSP_TYPE_ECHO, std::string("Echo"));
	fmod_sound->addDSP(0, std::string("Echo"));
	//fmod_sound->pauseChannel(0, true);
	//fmod_sound->stopChannel(0);
}