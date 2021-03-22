#include <iostream>
#include <OgreRoot.h>

void OGRE_Init()
{
	std::cout << "\n\n\nEMPIEZA LA INICIALIZACIÓN DE OGRE\n\n";

	Ogre::Root* root;
	root = new Ogre::Root();

	/*root->initialise(false);
	Ogre::SceneManager* scnMgr = root->createSceneManager();
	Ogre::Camera* cam = scnMgr->createCamera("myCam");*/
}