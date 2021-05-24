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

const int NFrames = 50;

class QUACK_ENGINE_PRO_API QuackTime {
private:
	double deltaTime_;
	double fixedDeltaTime_;
	double time_;
	double nextFixedTime_;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime_;


public:

	QuackTime();
	~QuackTime();

	bool frameStarted();

	double deltaTime();

	double fixedDeltaTime();

	double Time();
};

#endif
