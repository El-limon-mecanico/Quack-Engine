#include "AudioSource.h"
#include "SoundQuack.h"

AudioSource::AudioSource() :
	volume(0.5f)
{
	mngr_ = SoundQuack::Instance();
}

AudioSource::~AudioSource()
{
	mngr_ = nullptr;		// eliminar la referencia al Singleton
}

bool AudioSource::init(luabridge::LuaRef parameterTable)
{
	source = readVariable<std::string>(parameterTable, "Source");
	volume = readVariable<float>(parameterTable, "Volume");

	channel = mngr_->createSound(source, source);
	return true;
}

void AudioSource::play() {
	mngr_->playChannel(channel, source, volume);
}

void AudioSource::stop() {
	mngr_->stopChannel(channel);
}

void AudioSource::pause() {
	mngr_->pauseChannel(channel, true);
}

void AudioSource::resume() {
	mngr_->pauseChannel(channel, false);
}

bool AudioSource::isPlaying() {
	return mngr_->isPlaying(channel);
}

void AudioSource::setVolume(float value) {
	mngr_->setVolume(channel, volume);
}

float AudioSource::getVolume() {
	return mngr_->getVolume(channel);
}