#include "AudioListener.h"
#include "SoundQuack.h"
#include "Transform.h"
#include <fmod_common.h>


AudioListener::AudioListener()
{
	mngr_ = SoundQuack::Instance();
}

AudioListener::~AudioListener()
{
	if (index_ != -1)
		mngr_->removeListener(index_);
}

void AudioListener::preUpdate()
{
	if (index_ == -1)
		return;
	Vector3D pos = transform->position();
	Vector3D forward = transform->forward;
	Vector3D up = transform->up;
	mngr_->updateListener(index_, { pos.x,pos.y,pos.z }, { forward.x,forward.y,forward.z }, { up.x,up.y,up.z });
}

void AudioListener::onEnable()
{
	index_ = mngr_->getNewListener();

	//	System::set3DListenerAttributes
/*
	Vector3D pos = transform->position();
	Vector3D forward = transform->forward;
	Vector3D up = transform->up;

	// no se si hacer el getSystem o si esto lo hacemos desde SoundQuack(?)
	mngr_->getSystem()->set3DListenerAttributes(index_, pos, forward, up);
*/
}

void AudioListener::onDisable()
{
	if (index_ != -1)
		mngr_->removeListener(index_);
}
