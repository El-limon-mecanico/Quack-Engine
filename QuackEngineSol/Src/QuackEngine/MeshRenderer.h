#pragma once
#include "Component.h"

namespace Ogre {
	class Root;
	class SceneManager;
	class SceneNode;
	class Entity;
}

enum PrefabType {
	PT_PLANE,
	PT_CUBE,
	PT_SPHERE
};

class Render : public Component {
protected:
	Ogre::SceneNode* node_;
	Ogre::SceneManager* mSM_;
	Ogre::Entity* ogreEnt_;

	void setOgreEntity(Ogre::Entity* e);
	void setParent(Ogre::SceneNode* parent);

public:
	Render(QuackEntity* e = nullptr);
	~Render();

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setMeshByName(const std::string& name);
	
	Ogre::SceneNode* getNode() { return node_; }
	Ogre::SceneManager* getSceneManager() { return mSM_; }
	Ogre::Entity* getOgreEntity() { return ogreEnt_; }
	
	Ogre::Mesh* getMesh() const;
	
	void setVisible(bool visible);
};