#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
#include "LuaManager.h"
#include "FactoryManager.h"
#include <unordered_map>

namespace Ogre {
	class Root;
	class SceneManager;
	class SceneNode;
	class Entity;
}

class QuackEntity {

protected:
	Ogre::SceneNode* node_;
	Ogre::SceneManager* mSM_;
	Ogre::Entity* ogreEnt_;
private:
	bool active_;
	std::vector<Component*> components_;
	std::string tag_;
	std::unordered_map<std::string, Component*> cmpMap_;


public:
	QuackEntity(bool active = true, std::string tag = "Default");
	~QuackEntity();

	template<typename T, typename ... Targs>
	T* addComponent(Targs&&...mArgs) {
		T* c = new T(std::forward<Targs>(mArgs)...);
		c->setEntity(this);
		//c->init(readElementFromFile(("lua/Components/" + name + ".lua"), name));
		c->init();
		components_.push_back(c);
		//cmpMap_.insert({ name , c });
		return c;
	}

	//el component name es el nombre del componente como tal (mismo nombre para varias entidades con el mismo componente),
	//filename es el nombre del .lua de la entidad donde esta el prefab como tal
	Component* addComponent(const std::string& componentName, LuaRef param);
	Component* getComponent(const std::string& name);
	inline bool hasComponent(const std::string& name);
	inline bool isActive() const {
		return active_;
	}
	inline void setActive(bool state) {
		active_ = state;
	}
	void removeComponent(const std::string& name);
	Ogre::SceneNode* getNode() { return node_; }
	Ogre::SceneManager* getSceneManager() { return mSM_; }
	Ogre::Entity* getOgreEntity() { return ogreEnt_; }
	void setOgreEntity(Ogre::Entity* e);
	void setParent(Ogre::SceneNode* parent);
	void update();
};