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
	class Root;
	class SceneManager;
	class SceneNode;
	class Camera;
	class RenderWindow;
	class Viewport;
}
enum ProjectionType
{
	PT_ORTHOGRAPHIC,
	PT_PERSPECTIVE
};

class QUACK_ENGINE_PRO_API QuackCamera : public Component {
private:
	Ogre::SceneNode* node_ = nullptr;
	Ogre::SceneManager* mSM_ = nullptr;
	Ogre::RenderWindow* window_ = nullptr;
	Ogre::Camera* camera_ = nullptr;
	Ogre::Viewport* vp_ = nullptr;
	Vector3D target_ = Vector3D();
	Vector3D bg_ = Vector3D();
	std::string name_ = "DefaultCamera";
	std::string proj_ = "Perspective";
	int zOrder_ = 0;
	float width_ = 1;
	float height_ = 1;
	float near_ = 0;
	float far_ = 10000000;
	float top_ = 0;
	float left_ = 0;
	float xProp_ = 16;
	float yProp_ = 9;

public:
	QuackCamera(QuackEntity* e = nullptr);
	~QuackCamera();
	static std::string GetName() { return "Camera"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	virtual void onEnable();

	virtual void onDisable();

	Ogre::Camera* camera() { return camera_; }

	Ogre::Viewport* viewport() { return vp_; }

	void setzOrder(int zOrder);
};