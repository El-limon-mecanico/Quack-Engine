#include "AudioSource.h"
#include "SoundQuack.h"
#include <fmod_common.h>

AudioSource::AudioSource() :
	volume_(0.5f)
{
	mngr_ = SoundQuack::Instance();
}

AudioSource::~AudioSource()
{
	stop();
	mngr_ = nullptr;		// eliminar la referencia al Singleton
}

bool AudioSource::init(luabridge::LuaRef parameterTable)
{
	int loops = 0;
	bool correct = true;
	correct &= readVariable<std::string>(parameterTable, "Source", &source_);
	correct &= readVariable<float>(parameterTable, "Volume", &volume_);
	correct &= readVariable<int>(parameterTable, "Loops", &loops);
	bool sinceInit;
	correct &= readVariable<bool>(parameterTable, "Init", &sinceInit);
	if (!correct) return false;

	channel_ = mngr_->createSound(source_, source_, FMOD_DEFAULT);
	if (channel_ == -1) {
		std::cout << "ERROR: Couldn't create sound\n";
		return false;
	}
	setVolume(volume_);
	if (loops >= -1)	loop(loops);
	else std::cout << "	WARNING: loop count must be >= -1\n";
	if(sinceInit)
		play();

	return correct;
}

void AudioSource::play() {
	mngr_->playChannel(channel_, source_, volume_);
}

void AudioSource::stop() {
	mngr_->stopChannel(channel_);
}

void AudioSource::pause() {
	mngr_->pauseChannel(channel_, true);
}

void AudioSource::resume() {
	mngr_->pauseChannel(channel_, false);
}

bool AudioSource::isPlaying() {
	return mngr_->isPlaying(channel_);
}

void AudioSource::loop(int times)
{
	mngr_->setMode(channel_, mngr_->getMode(channel_) | FMOD_LOOP_NORMAL, source_);
	mngr_->loop(channel_, times, source_);
}

int AudioSource::getCurrentLoop() {
	return mngr_->getCurrentLoop(channel_);
}

void AudioSource::setVolume(float value) {
	mngr_->setVolume(channel_, value);
}

float AudioSource::getVolume() {
	return mngr_->getVolume(channel_);
}