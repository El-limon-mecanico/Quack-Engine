#pragma once
#include "Component.h"

//no se si esto es lo correcto para acceder a las clases que necesito?¿?¿?¿
namespace Ogre {
	class Root;
	class SceneManager;
	class SceneNode;
}

enum PrefabType {
	PT_PLANE,
	PT_CUBE,
	PT_SPHERE
};

class RenderComponent : public Component {
private:
	Ogre::SceneManager* mSM_;
public:
	RenderComponent(QuackEntity* e = nullptr);
	~RenderComponent();

	virtual bool init(luabridge::LuaRef parameterTable);

	void setMeshByPrefab(PrefabType prefab);

	void setMeshByName(const std::string& name);
};