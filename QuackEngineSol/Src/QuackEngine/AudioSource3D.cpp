#include "AudioSource3D.h"
#include "SoundQuack.h"

AudioSource3D::AudioSource3D() :
	volume(0.5f)
{
	mngr_ = SoundQuack::Instance();
}

AudioSource3D::~AudioSource3D()
{
	mngr_ = nullptr;		// eliminar la referencia al Singleton
}

bool AudioSource3D::init(luabridge::LuaRef parameterTable)
{
	source = readVariable<std::string>(parameterTable, "AudioSource");
	volume = readVariable<float>(parameterTable, "Volume");

	channel = mngr_->createSound(source, source);
	return true;
}

void AudioSource3D::play() {
	mngr_->playChannel(channel, source, volume);
}

void AudioSource3D::stop() {
	mngr_->stopChannel(channel);
}

void AudioSource3D::pause() {
	mngr_->pauseChannel(channel, true);
}

void AudioSource3D::resume() {
	mngr_->pauseChannel(channel, false);
}

bool AudioSource3D::isPlaying() {
	return mngr_->isPlaying(channel);
}

void AudioSource3D::setVolume(float value) {
	mngr_->setVolume(channel, volume);
}

float AudioSource3D::getVolume() {
	return mngr_->getVolume(channel);
}