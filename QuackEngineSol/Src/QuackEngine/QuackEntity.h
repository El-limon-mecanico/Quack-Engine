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
}

class QuackEntity {

protected:

private:
	bool active_;
	std::vector<Component*> components_;
	std::string tag_;
	std::unordered_map<std::string, Component*> cmpMap_;
	Ogre::SceneNode* node_;

public:
	QuackEntity(bool active = true, std::string tag = "Default");
	~QuackEntity();

	template<typename T>
	T* addComponent(const std::string& name) {
		/*if (hasComponent(name))
			return cmpMap_[name];*/
			/*else {*/
		T* c = FactoryManager::instance()->create<T>(name);
		c->setEntity(this);
		c->init(readLuaFile(("lua/Components/" + name + ".lua"), name));
		components_.push_back(c);
		cmpMap_.insert({ name , c });
		return c;
		/*}*/
	}

	Component* addComponent(const std::string& name);
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
	void setParent(Ogre::SceneNode* parent);
	void update();
};
