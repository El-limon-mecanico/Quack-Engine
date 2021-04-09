#include "BULLET.h"
#include "BtOgre.h"
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <iostream>

using namespace BtOgre;

void BULLET_Init() {

	SDL_Init(SDL_INIT_EVERYTHING);

	if (!SDL_WasInit(SDL_INIT_VIDEO))
		SDL_InitSubSystem(SDL_INIT_VIDEO);


	Ogre::Root* root;
	root = new Ogre::Root();

	root->showConfigDialog(NULL);

	root->initialise(false);

	Ogre::RenderWindow* mWindow;


	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE

	SDL_Window* sdlWindow = SDL_CreateWindow("COSAS DE VENTANEAR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}
	Ogre::ConfigOptionMap CurrentGraphicsConfiguration = root->getRenderSystem()->getConfigOptions();

	Ogre::NameValuePairList params;

	params["FSAA"] = CurrentGraphicsConfiguration["FSAA"].currentValue;
	params["vsync"] = CurrentGraphicsConfiguration["VSync"].currentValue;
	params["gamma"] = CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue;

	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));


	mWindow = root->createRenderWindow("COSAS DE VENTANEAR", 800, 600, false, &params);

	SDL_SetWindowGrab(sdlWindow, SDL_bool(false));
	SDL_ShowCursor(true);

	Ogre::SceneManager* mSM;

	mSM = root->createSceneManager();

	Ogre::Camera* mCamera;

	mCamera = mSM->createCamera("MainCam");

	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(100000);
	mCamera->setAutoAspectRatio(true);


	Ogre::SceneNode* mNodeCamera = mSM->getRootSceneNode()->createChildSceneNode();
	mNodeCamera->attachObject(mCamera);

	mNodeCamera->setPosition(200, 0, 0);
	mNodeCamera->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(1, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	mSM->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	root->startRendering();


	Ogre::Entity* a = mSM->createEntity(Ogre::SceneManager::PrefabType::PT_CUBE);

	Ogre::SceneNode* mNode = mSM->getRootSceneNode()->createChildSceneNode();

	mNode->attachObject(a);


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
	}

	//while (true)
	//{
	//	// OgreBites::WindowEventUtilities::messagePump();  WindowEventUtilities se ha mudado con el traidor OgreBites y no sabemos como sustituir esta linea

	//	if (mWindow->isClosed()) return;

	//	if (!root->renderOneFrame()) return;
	//}
}