#include "AudioSource3D.h"
#include "SoundQuack.h"

AudioSource3D::AudioSource3D() :
	volume_(0.5f)
{
	mngr_ = SoundQuack::Instance();
}

AudioSource3D::~AudioSource3D()
{
	mngr_ = nullptr;		// eliminar la referencia al Singleton
}

bool AudioSource3D::init(luabridge::LuaRef parameterTable)
{
	source_ = readVariable<std::string>(parameterTable, "AudioSource");
	volume_ = readVariable<float>(parameterTable, "Volume");

	channel_ = mngr_->createSound(source_, source_);
	return true;
}

void AudioSource3D::play() {
	mngr_->playChannel(channel_, source_, volume_);
}

void AudioSource3D::stop() {
	mngr_->stopChannel(channel_);
}

void AudioSource3D::pause() {
	mngr_->pauseChannel(channel_, true);
}

void AudioSource3D::resume() {
	mngr_->pauseChannel(channel_, false);
}

bool AudioSource3D::isPlaying() {
	return mngr_->isPlaying(channel_);
}

void AudioSource3D::setVolume(float value) {
	mngr_->setVolume(channel_, volume_);
}

float AudioSource3D::getVolume() {
	return mngr_->getVolume(channel_);
}