#include "Light.h"
#include "OgreQuack.h"
#include "Transform.h"
#include <OgreLight.h>
#include <OgreSceneNode.h>

Light::Light() :
	light_(nullptr),
	node_(nullptr)
{
}

Light::~Light()
{
	delete light_;
	light_ = nullptr;
}

void Light::setAmbientLight(Vector3D light)
{
	OgreQuack::Instance()->setAmbientLight(light.x, light.y, light.z);
}

bool Light::init(luabridge::LuaRef parameterTable)
{
	lightType_ = (LightType)readVariable<int>(parameterTable, "LightType");
	LuaRef dColor = readVariable<LuaRef>(parameterTable, "DiffuseColor");
	LuaRef sColor = readVariable<LuaRef>(parameterTable, "SpecularColor");
	LuaRef dir = readVariable<LuaRef>(parameterTable, "Direction");
	powerLevel_ = readVariable<float>(parameterTable, "PowerLevel");
	innerAngle_ = readVariable<float>(parameterTable, "InnerAngle");
	outerAngle_ = readVariable<float>(parameterTable, "OuterAngle");
	isOn = readVariable<bool>(parameterTable, "isOn");

	diffuseColor_ = Vector3D(dColor[1], dColor[2], dColor[3]);
	specularColor_ = Vector3D(sColor[1], sColor[2], sColor[3]);
	direction_ = Vector3D(dir[1], dir[2], dir[3]);

	return true;
}

void Light::onEnable()
{
	if (firstEnable) {
		light_ = OgreQuack::Instance()->createLigth((Ogre::LightTypes)lightType_);
		node_ = transform->getNode()->createChildSceneNode();
		node_->attachObject(light_);
		node_->lookAt(Vector3D::toOgre(direction_), Ogre::Node::TransformSpace::TS_WORLD);

		light_->setDiffuseColour(diffuseColor_.x, diffuseColor_.y, diffuseColor_.z);
		light_->setSpecularColour(specularColor_.x, specularColor_.y, specularColor_.z);
		light_->setPowerScale(powerLevel_);
		if (lightType_ = SPOTLIGHT) {
			light_->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
			light_->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
		}
		firstEnable = false;
	}
	light_->setVisible(isOn);
}

void Light::onDisable()
{
	light_->setVisible(false);
}

void Light::setDiffuseColor(Vector3D color)
{
	diffuseColor_ = color;
	light_->setDiffuseColour(color.x, color.y, color.z);
}

void Light::setSpecularColor(Vector3D color)
{
	specularColor_ = color;
	light_->setSpecularColour(color.x, color.y, color.z);
}

void Light::setDirection(Vector3D orientation, bool global)
{
	direction_ = orientation;
	node_->lookAt(Vector3D::toOgre(direction_), global ?
		Ogre::Node::TransformSpace::TS_WORLD :
		Ogre::Node::TransformSpace::TS_LOCAL);
}

void Light::setType(LightType type)
{
	light_->setType((Ogre::Light::LightTypes)type);
	if(lightType_ = SPOTLIGHT){
		light_->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
		light_->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
	}
}

void Light::setPowerLevel(float powerLevel)
{
	powerLevel_ = powerLevel;
	light_->setPowerScale(powerLevel);
}

void Light::setInnerAngle(float angle)
{
	innerAngle_ = angle;
	if (lightType_ = SPOTLIGHT)
		light_->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
}

void Light::setOuterAngle(float angle)
{
	outerAngle_ = angle;
	if (lightType_ = SPOTLIGHT)
		light_->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
}
