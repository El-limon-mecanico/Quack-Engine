#include "QuackCamera.h"
#include "QuackEntity.h"
#include "OgreQuack.h"
#include <Ogre.h>

QuackCamera::QuackCamera(QuackEntity* e) : Component(e), camera_(nullptr), target_(0,0,0)
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
	LuaRef color = readVariable<LuaRef>(parameterTable, "Background");
	Vector3D bg = (color[1], color[2], color[3]);
	LuaRef look = readVariable<LuaRef>(parameterTable, "LookAt");
	target_ = Vector3D(look[1], look[2], look[3]);
	//float width = readVariable<float>(parameterTable, "Width"); 
	//float height = readVariable<float>(parameterTable, "Height");

	initCamera(name, bg);

	return true;
}

void QuackCamera::start()
{
	node_->attachObject(camera_);
	node_->lookAt(Vector3D::toOgre(target_), Ogre::Node::TS_WORLD);
}

void QuackCamera::onEnable()
{
	if (firstEnable_) {
		node_ = transform->getNode();
		firstEnable_ = false;
	}
}

void QuackCamera::onDisable()
{
	//aquí al igual habria que desactivar algo de la camara
}

void QuackCamera::initCamera(std::string name, Vector3D bg) {
	//TODO HACER QUE PUEDA TENER VIEWPORTS DIFERENTES AL DEL WINDOW?¿
	camera_ = mSM_->createCamera(name);
	camera_->setNearClipDistance(1);
	camera_->setFarClipDistance(100000);
	camera_->setAutoAspectRatio(true);
	vp_ = window_->addViewport(camera_);
	vp_->setBackgroundColour(Ogre::ColourValue(bg.x, bg.y, bg.z));
	camera_->setAspectRatio(
		Ogre::Real(vp_->getActualWidth()) /
		Ogre::Real(vp_->getActualHeight()));
}