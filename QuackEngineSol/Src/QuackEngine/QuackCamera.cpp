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
}

bool QuackCamera::init(luabridge::LuaRef parameterTable)
{
	std::string name = readVariable<std::string>(parameterTable, "Name");
	LuaRef bgc = readVariable<LuaRef>(parameterTable, "Background");
	LuaRef look = readVariable<LuaRef>(parameterTable, "LookAt");
	target_ = Vector3D(look[1], look[2], look[3]);
	Vector3D bg = { bgc[1], bgc[2], bgc[3] };
	int width = readVariable<float>(parameterTable, "Width");
	int height = readVariable<float>(parameterTable, "Height");
	float near = readVariable<float>(parameterTable, "NearClipDistance");
	float far = readVariable<float>(parameterTable, "FarClipDistance");
	std::string proj = readVariable<std::string>(parameterTable, "ProjectionType");

	camera_ = mSM_->createCamera(name);
	camera_->setNearClipDistance(near);
	camera_->setFarClipDistance(far);
	camera_->setAutoAspectRatio(true);

	if (proj == "Orthographic")
		camera_->setProjectionType(Ogre::ProjectionType::PT_ORTHOGRAPHIC);
	else
		camera_->setProjectionType(Ogre::ProjectionType::PT_PERSPECTIVE);

	vp_ = window_->addViewport(camera_);
	vp_->setBackgroundColour(Ogre::ColourValue(bg.x, bg.y, bg.z));

	if (width == 0) width = vp_->getActualWidth();
	if (height == 0) height = vp_->getActualHeight();
	camera_->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));

	return true;
}

void QuackCamera::onEnable()
{
	if (firstEnable_)
	{
		node_ = entity_->transform()->getNode()->createChildSceneNode();
		node_->attachObject(camera_);
		node_->lookAt(target_.toOgrePosition(), Ogre::Node::TS_WORLD);
		firstEnable_ = false;
	}

}
