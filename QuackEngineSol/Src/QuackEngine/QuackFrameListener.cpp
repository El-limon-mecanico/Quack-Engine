#include "QuackFrameListener.h"
#include <OgreTimer.h>
//#include <Windows.h>




QuackFrameListener::QuackFrameListener()
{
	timer_ = new Ogre::Timer();
	lastFrameTime_ = std::chrono::high_resolution_clock::now();
}


QuackFrameListener::~QuackFrameListener()
{
	delete timer_;
	timer_ = nullptr;
}

bool QuackFrameListener::frameStarted(const Ogre::FrameEvent& evt)
{
	return false;
}
