#ifndef _QUACK_FRAME_LISTENER_
#define _QUACK_FRAME_LISTENER_

#include <chrono>

class QuackTime {
private:
	double deltaTime_;
	double time;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime_;


public:

	QuackTime();
	~QuackTime();

	void frameStarted();

	double deltaTime();

	double Time();

};

#endif
