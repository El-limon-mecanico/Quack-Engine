#include "QuackTime.h"
#include <OgreTimer.h>
#include "QuackEnginePro.h"
//#include <Windows.h>

QuackTime::QuackTime() : deltaTime_(0)
{
	lastFrameTime_ = std::chrono::high_resolution_clock::now();
}


QuackTime::~QuackTime()
{
}

double QuackTime::deltaTime() {
	return deltaTime_;
}

void QuackTime::frameStarted()
{
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - lastFrameTime_;

	deltaTime_ = elapsed.count();

	lastFrameTime_ = std::chrono::high_resolution_clock::now();
}
