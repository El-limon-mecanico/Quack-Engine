#include <iostream>
#include <OgreRoot.h>


void OGRE_Init()
{
	std::cout << "\n\n\nEMPIEZA LA INICIALIZACIÓN DE OGRE\n\n";

	//paso 1 -> crear root
	Ogre::Root* root;
	root = new Ogre::Root();
	//paso 2 -> crear renderwindow
	Ogre::RenderWindow* mWindow;
	//paso 3 -> configurar rendersystem
	Ogre::RenderSystem* rs = root->getRenderSystemByName("Direct3D11 Rendering Subsystem");
	root->setRenderSystem(rs);
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	//paso 4-> magic
	mWindow = root->initialise(true, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	
	/*Ogre::SceneManager* scnMgr = root->createSceneManager();
	Ogre::Camera* cam = scnMgr->createCamera("myCam");*/
}