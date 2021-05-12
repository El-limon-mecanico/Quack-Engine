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
	class Entity;
	class Mesh;
}

enum PrefabType {
	PT_PLANE,
	PT_CUBE,
	PT_SPHERE
};

class QUACK_ENGINE_PRO_API MeshRenderer : public Component {
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