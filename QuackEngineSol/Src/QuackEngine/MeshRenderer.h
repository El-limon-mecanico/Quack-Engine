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
private:
	Ogre::SceneNode* node_;
	Ogre::SceneManager* mSM_;
	Ogre::Entity* ogreEnt_;
	std::string materialName_;

	bool firstEnable_ = true;
	bool visible_ = true;
public:
	MeshRenderer(QuackEntity* e = nullptr);
	~MeshRenderer();

	static std::string GetName() { return "MeshRenderer"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setMeshByPrefab(PrefabType prefab);
	void setMeshByName(const std::string& name);

	Ogre::SceneManager* getSceneManager() { return mSM_; }
	Ogre::Entity* getOgreEntity() { return ogreEnt_; }
	
	Ogre::Mesh* getMesh() const;
	
	void setVisible(bool visible);
	void setMaterial(std::string materialName);

	virtual void onEnable() override;

	virtual void onDisable() override;
};