#include "QuackTime.h"
#include <OgreTimer.h>
#include "QuackEnginePro.h"
//#include <Windows.h>

QuackTime::QuackTime() :
	deltaTime_(0), time_(0),
	nextFixedTime_(0), fixedDeltaTime_(1.0 / NFrames)
{
	lastFrameTime_ = std::chrono::high_resolution_clock::now();
}


QuackTime::~QuackTime()
{
}

double QuackTime::deltaTime() {
	return deltaTime_;
}

double QuackTime::fixedDeltaTime()
{
	return fixedDeltaTime_;
}

double QuackTime::Time()
{
	return time_;
}

bool QuackTime::frameStarted()
{
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - lastFrameTime_;

	deltaTime_ = elapsed.count();

	time_ += deltaTime_;

	lastFrameTime_ = std::chrono::high_resolution_clock::now();

	if (time_ >= nextFixedTime_) {
		nextFixedTime_ = time_ + fixedDeltaTime_;
		return true;
	}
	return false;
}


