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
	bool playOnStart=false;
	correct &= readVariable<bool>(parameterTable, "Play", &playOnStart);
	if (!correct) return false;

	channel_ = mngr_->createSound(source_, source_, FMOD_DEFAULT);
	if (channel_ == -1) {
		std::cout << "ERROR: Couldn't create sound\n";
		return false;
	}
	setVolume(volume_);
	if (loops >= -1)	loop(loops);
	else std::cout << "	WARNING: loop count must be >= -1\n";
	if (playOnStart)
		play();

	return correct;
}

void AudioSource::onEnable()
{
	if (playing_)
		resume();
}

void AudioSource::onDisable()
{
	if (playing_) {
		pause();
		playing_ = true;
	}
}

void AudioSource::play() {
	playing_ = true;
	mngr_->playChannel(channel_, source_, volume_);
}

void AudioSource::stop() {
	playing_ = false;
	mngr_->stopChannel(channel_);
}

void AudioSource::pause() {
	playing_ = false;
	mngr_->pauseChannel(channel_, true);
}

void AudioSource::resume() {
	playing_ = true;
	mngr_->pauseChannel(channel_, false);
}

bool AudioSource::isPlaying() {
	return playing_;
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