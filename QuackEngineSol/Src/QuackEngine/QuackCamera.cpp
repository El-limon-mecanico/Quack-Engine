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
	if (camera_)
		mSM_->destroyCamera(camera_);
	if (window_->hasViewportWithZOrder(zOrder_) && vp_)
		window_->removeViewport(zOrder_);
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
	bool correct = true;

	correct &= readVariable<std::string>(parameterTable, "Name", &name_);
	correct &= readVariable<LuaRef>(parameterTable, "Background", &bgc);
	correct &= readVariable<LuaRef>(parameterTable, "LookAt", &look);
	correct &= readVariable<float>(parameterTable, "Width", &width_);
	correct &= readVariable<float>(parameterTable, "Height", &height_);
	correct &= readVariable<float>(parameterTable, "NearClipDistance", &near_);
	correct &= readVariable<float>(parameterTable, "FarClipDistance", &far_);
	correct &= readVariable<float>(parameterTable, "Top", &top_);
	correct &= readVariable<float>(parameterTable, "Left", &left_);
	correct &= readVariable<float>(parameterTable, "xProp", &xProp_);
	correct &= readVariable<float>(parameterTable, "yProp", &yProp_);
	correct &= readVariable<std::string>(parameterTable, "ProjectionType", &proj_);
	correct &= readVariable<int>(parameterTable, "zOrder", &zOrder_);

	if (!correct) return false;

	target_ = Vector3D(look[1], look[2], look[3]);
	bg_ = { bgc[1], bgc[2], bgc[3] };


	if (width_ == 0) width_ = 1;
	if (width_ == 0) height_ = 1;

	float ratio = ((float)window_->getWidth() / window_->getHeight()) / (xProp_ / yProp_);
	height_ *= ratio;

	node_ = entity_->transform()->getNode()->createChildSceneNode();
	node_->lookAt(target_.toOgrePosition(), Ogre::Node::TS_WORLD);

	return true;
}

void QuackCamera::onEnable()
{
	camera_ = mSM_->createCamera(name_);
	camera_->setNearClipDistance(near_);
	camera_->setFarClipDistance(far_);
	camera_->setAutoAspectRatio(true);

	camera_->setProjectionType((proj_ == "Orthographic") ? Ogre::ProjectionType::PT_ORTHOGRAPHIC : Ogre::ProjectionType::PT_PERSPECTIVE);

	camera_->setAspectRatio(xProp_ / yProp_);

	node_->attachObject(camera_);

	setzOrder(zOrder_);
}

void QuackCamera::onDisable()
{
	if (camera_) {
		node_->detachObject(camera_);
		mSM_->destroyCamera(camera_);
		camera_ = nullptr;
	}
	if (window_->hasViewportWithZOrder(zOrder_) && vp_) {
		window_->removeViewport(zOrder_);
		vp_ = nullptr;
	}
}

void QuackCamera::setzOrder(int zOrder)
{
	while (true) {
		if (!window_->hasViewportWithZOrder(zOrder))
			break;
		std::cout << "\tWARNING: ya existe una camara con zOrder " << zOrder << ", cambia el zOrder en la entidad " << entity_->name() << "\n";
		zOrder++;
		std::cout << "\tMoviendo zOrder de " << entity_->name() << " a " << zOrder << "\n";
	}

	zOrder_ = zOrder;

	vp_ = window_->addViewport(camera_, zOrder_, left_, top_, width_, height_);
	vp_->setBackgroundColour(Ogre::ColourValue(bg_.x, bg_.y, bg_.z));
}