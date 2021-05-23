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
	Vector3D target_;
	
public:
	QuackCamera(QuackEntity* e = nullptr);
	~QuackCamera();
	static std::string GetName() { return "Camera"; }
	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });
	Ogre::Camera* camera() { return camera_; }
	Ogre::Viewport* viewport() { return vp_; }
};