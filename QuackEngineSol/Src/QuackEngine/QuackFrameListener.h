#ifndef _QUACK_FRAME_LISTENER_
#define _QUACK_FRAME_LISTENER_

#include <OgreFrameListener.h>
#include <chrono>

namespace Ogre {
	class Timer;
}

class QuackFrameListener : Ogre::FrameListener {
private:

	Ogre::Timer* timer_;
	double deltaTime_;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime_;

public:

	QuackFrameListener();
	~QuackFrameListener();

	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }
	virtual void windowMoved(Ogre::RenderWindow* rw) {}
	virtual void windowResized(Ogre::RenderWindow* rw) {}
	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }
	virtual void windowClosed(Ogre::RenderWindow* rw) {}
	virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

	double DeltaTime() { return deltaTime_; }

};

#endif
