#include "AudioSource.h"
#include "SoundQuack.h"
#include "Transform.h"
#include <fmod_common.h>

AudioSource::AudioSource() :
	volume_(0.5f)
{
	mngr_ = SoundQuack::Instance();
}

AudioSource::~AudioSource()
{
	mngr_->removeSound(sound_);
	mngr_ = nullptr;		// eliminar la referencia al Singleton
}

bool AudioSource::init(luabridge::LuaRef parameterTable)
{
	int loops = 0;
	bool correct = true;
	bool playOnStart = false;
	correct &= readVariable<std::string>(parameterTable, "Source", &source_);
	correct &= readVariable<float>(parameterTable, "Volume", &volume_);
	correct &= readVariable<int>(parameterTable, "Loops", &loops);
	correct &= readVariable<bool>(parameterTable, "Play", &playOnStart);
	correct &= readVariable<bool>(parameterTable, "3D", &D3_);
	if (!correct) return false;

	sound_ = mngr_->createSound(source_, D3_ ? FMOD_3D : FMOD_DEFAULT);
	if (!sound_) {
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

void AudioSource::preUpdate()
{
	if(D3_){
		Vector3D pos = transform->position();
		mngr_->set3DTransform(sound_, { pos.x,pos.y,pos.z });
	}
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
	if (!playing_) {
		playing_ = true;
		mngr_->playSound(sound_, volume_);
	}

}

void AudioSource::stop() {
	playing_ = false;
	mngr_->stopSound(sound_);
}

void AudioSource::pause() {
	playing_ = false;
	mngr_->pauseSound(sound_, true);
}

void AudioSource::resume() {
	playing_ = true;
	mngr_->pauseSound(sound_, false);
}

bool AudioSource::isPlaying() {
	return playing_;
}

void AudioSource::loop(int times)
{
	mngr_->setMode(sound_, mngr_->getMode(sound_) | FMOD_LOOP_NORMAL);
	mngr_->loop(sound_, times);
}

int AudioSource::getCurrentLoop() {
	return mngr_->getCurrentLoop(sound_);
}

void AudioSource::setVolume(float value) {
	mngr_->setVolume(sound_, value);
}

float AudioSource::getVolume() {
	return mngr_->getVolume(sound_);
}