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
	Ogre::SceneNode* node_;
	Ogre::SceneManager* mSM_;
	Ogre::RenderWindow* window_;
	Ogre::Camera* camera_;
	Ogre::Viewport* vp_;
	Vector3D target_;
	bool firstEnable_;
	//void initCamera(std::string name, Vector3D bg, Vector3D target, int width, int height, float near, float far, std::string );

public:
	QuackCamera(QuackEntity* e = nullptr);
	~QuackCamera();
	static std::string GetName() { return "Camera"; }
	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });
	Ogre::Camera* camera() { return camera_; }
	Ogre::Viewport* viewport() { return vp_; }
};