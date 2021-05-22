#include "Light.h"
#include "OgreQuack.h"
#include "Transform.h"
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


Light::Light() :
	light_(nullptr),
	node_(nullptr)
{
}

Light::~Light()
{
	OgreQuack::Instance()->getSceneManager()->destroyLight(light_);
	light_ = nullptr;
}

void Light::setAmbientLight(Vector3D light)
{
	OgreQuack::Instance()->setAmbientLight(light.x, light.y, light.z);
}

bool Light::init(luabridge::LuaRef parameterTable)
{
	LuaRef dColor = NULL, sColor = NULL, dir = NULL;
	bool correct = true;
	
	const int* a;
	int b;
	a = &b;
	*a++;

	correct &= readVariable<int>(parameterTable, "LightType", (int*)(&lightType_));
	correct &= readVariable<LuaRef>(parameterTable, "DiffuseColor", &dColor);
	correct &= readVariable<LuaRef>(parameterTable, "SpecularColor", &sColor);
	correct &= readVariable<LuaRef>(parameterTable, "Direction", &dir);
	correct &= readVariable<float>(parameterTable, "Distance", &distance_);
	correct &= readVariable<float>(parameterTable, "InnerAngle", &innerAngle_);
	correct &= readVariable<float>(parameterTable, "OuterAngle", &outerAngle_);
	correct &= readVariable<bool>(parameterTable, "isOn", &isOn);

	if (!correct) return false;
	
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
		node_->lookAt(direction_.toOgrePosition(), Ogre::Node::TransformSpace::TS_WORLD);

		light_->setDiffuseColour(diffuseColor_.x, diffuseColor_.y, diffuseColor_.z);
		light_->setSpecularColour(specularColor_.x, specularColor_.y, specularColor_.z);
		light_->setCastShadows(true);
		setDistance(distance_);
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
	if (lightType_ = SPOTLIGHT) {
		light_->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
		light_->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(innerAngle_)));
	}
}

void Light::setDistance(float distance)
{
	distance_ = distance;
	float linear = 4.5 / distance;
	float quadratic = 75.0 / pow(pow(distance_, 3), 2);

	light_->setAttenuation(pow(distance_, 3), 0.8, linear, quadratic);
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
