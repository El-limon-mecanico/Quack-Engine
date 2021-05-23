#include "QuackCamera.h"
#include "QuackEntity.h"
#include "OgreQuack.h"
#include <Ogre.h>

QuackCamera::QuackCamera(QuackEntity* e) : Component(e), camera_(nullptr)
{
	mSM_ = OgreQuack::Instance()->getSceneManager();
	window_ = OgreQuack::Instance()->getWindow();
}

QuackCamera::~QuackCamera()
{
	mSM_->destroyCamera(camera_);
	window_->removeViewport(vp_->getZOrder());
	camera_ = nullptr;
	node_ = nullptr;
	mSM_ = nullptr;
	window_ = nullptr;
	vp_ = nullptr;

}

bool QuackCamera::init(luabridge::LuaRef parameterTable)
{
	std::string name, proj;
	LuaRef bgc = NULL, look = NULL;
	Vector3D bg(0.0);
	int width = 0, height = 0;
	float near = 0, far = 0;
	bool correct = true;
	
	correct &= readVariable<std::string>(parameterTable, "Name", &name);
	correct &= readVariable<LuaRef>(parameterTable, "Background", &bgc);
	correct &= readVariable<LuaRef>(parameterTable, "LookAt", &look);
	correct &= readVariable<int>(parameterTable, "Width", &width);
	correct &= readVariable<int>(parameterTable, "Height", &height);
	correct &= readVariable<float>(parameterTable, "NearClipDistance", &near);
	correct &= readVariable<float>(parameterTable, "FarClipDistance", &far);
	correct &= readVariable<std::string>(parameterTable, "ProjectionType", &proj);

	if (!correct) return false;

	target_ = Vector3D(look[1], look[2], look[3]);
	bg = { bgc[1], bgc[2], bgc[3] };

	camera_ = mSM_->createCamera(name);
	camera_->setNearClipDistance(near);
	camera_->setFarClipDistance(far);
	camera_->setAutoAspectRatio(true);

	camera_->setProjectionType((proj == "Orthographic") ? Ogre::ProjectionType::PT_ORTHOGRAPHIC : Ogre::ProjectionType::PT_PERSPECTIVE);

	vp_ = window_->addViewport(camera_);
	vp_->setBackgroundColour(Ogre::ColourValue(bg.x, bg.y, bg.z));

	if (width == 0) width = vp_->getActualWidth();
	if (height == 0) height = vp_->getActualHeight();
	camera_->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));

	node_ = entity_->transform()->getNode()->createChildSceneNode();
	node_->attachObject(camera_);
	node_->lookAt(target_.toOgrePosition(), Ogre::Node::TS_WORLD);

	return true;
}
