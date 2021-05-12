#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include "Component.h"

namespace Ogre {
	class Light;
	class SceneNode;
}

enum LightType
{
	POINTLIGHT = 0,
	DIRECTIONALLIGHT = 1,
	SPOTLIGHT = 2
};

class QUACK_ENGINE_PRO_API Light : public Component {
private:

	Ogre::SceneNode* node_;

	Ogre::Light* light_;

	LightType lightType_;

	Vector3D diffuseColor_;
	Vector3D specularColor_;

	Vector3D direction_;

	float powerLevel_;

	float innerAngle_;

	float outerAngle_;

	bool isOn = true;

	bool firstEnable = true;

public:

	Light();
	~Light();

	static std::string GetName() { return "Light"; }

	static void setAmbientLight(Vector3D light);

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void onEnable() override;

	virtual void onDisable() override;

	void setDiffuseColor(Vector3D color);

	void setSpecularColor(Vector3D color);

	// FUNCIONA COMO UN LOOK AT
	void setDirection(Vector3D direction, bool global = true);

	void setType(LightType type);

	void setPowerLevel(float powerLevel);

	// FUNCIONA SOLO CON SPOTLIGHT
	void setInnerAngle(float angle);

	// FUNCIONA SOLO CON SPOTLIGHT
	void setOuterAngle(float angle);

};