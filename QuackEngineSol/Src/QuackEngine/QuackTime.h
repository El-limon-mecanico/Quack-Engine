#ifndef _QUACK_FRAME_LISTENER_
#define _QUACK_FRAME_LISTENER_

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <chrono>

class QUACK_ENGINE_PRO_API QuackTime {
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
