#pragma once
#include "Component.h"

//no se si esto es lo correcto para acceder a las clases que necesito?�?�?�
namespace Ogre {
	class Root;
	class SceneManager;
	class SceneNode;
	class Entity;
	class Mesh;
}

enum PrefabType {
	PT_PLANE,
	PT_CUBE,
	PT_SPHERE
};

class MeshRenderer : public Component {
public:
	MeshRenderer(QuackEntity* e = nullptr);
	~MeshRenderer();

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setMeshByPrefab(PrefabType prefab);

	void setMeshByName(const std::string& name);

	Ogre::Mesh* getMesh() const;

	void setVisible(bool visible);
};