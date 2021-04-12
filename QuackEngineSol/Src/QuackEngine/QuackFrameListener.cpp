#include "QuackFrameListener.h"
#include <OgreTimer.h>
#include "QuackEnginePro.h"
//#include <Windows.h>




QuackFrameListener::QuackFrameListener() : Ogre::FrameListener(), deltaTime_(0)
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
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - lastFrameTime_;

	deltaTime_ = elapsed.count();

	lastFrameTime_ = std::chrono::high_resolution_clock::now();

	QuackEnginePro::instance()->update();

	return true;
}
