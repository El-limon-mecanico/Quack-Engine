#pragma once

#include "Component.h"

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
protected:
	Ogre::SceneNode* node_;
	Ogre::SceneManager* mSM_;
	Ogre::Entity* ogreEnt_;

	void setOgreEntity(Ogre::Entity* e);
	void setParent(Ogre::SceneNode* parent);

public:
	MeshRenderer(QuackEntity* e = nullptr);
	~MeshRenderer();

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setMeshByPrefab(PrefabType prefab);
	void setMeshByName(const std::string& name);
	
	Ogre::SceneNode* getNode() { return node_; }
	Ogre::SceneManager* getSceneManager() { return mSM_; }
	Ogre::Entity* getOgreEntity() { return ogreEnt_; }
	
	Ogre::Mesh* getMesh() const;
	
	void setVisible(bool visible);
};