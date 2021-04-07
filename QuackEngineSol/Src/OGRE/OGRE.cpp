#include <iostream>
#include <OgreRoot.h>
#include "FMOD_Quack.h"


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

void prueba(fmod_quack* fmod_sound)
{
	fmod_sound->createSound(std::string("singing.wav"), "Cantando");
	fmod_sound->playSound(0, "Cantando", 1);
	fmod_sound->createDSP(FMOD_DSP_TYPE_ECHO, std::string("Echo"));
	fmod_sound->addDSP(0, std::string("Echo"));
	fmod_sound->pauseChannel(0, false);
}
