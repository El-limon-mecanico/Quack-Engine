#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Transform.h"
#include <unordered_map>

namespace luabridge {
	class LuaRef;
}

namespace Ogre {
	class Root;
	class SceneManager;
	class SceneNode;
	class Entity;
}

class QuackEntity {
private:
	bool active_;
	std::vector<Component*> components_;
	std::string tag_;
	std::string name_;
	std::unordered_map<std::string, Component*> cmpMap_;
	Transform* transform_;

public:
	QuackEntity(std::string name = "DefaultName", bool active = true, std::string tag = "Default");
	~QuackEntity();

	template<typename T, typename ... Targs>
	T* addComponent(Targs&&...mArgs) {
		T* c = new T(std::forward<Targs>(mArgs)...);
		c->setEntity(this);
		components_.push_back(c);
		cmpMap_.insert({ T::GetName() , c });
		return c;
	}

	//el component name es el nombre del componente como tal (mismo nombre para varias entidades con el mismo componente),
	//filename es el nombre del .lua de la entidad donde esta el prefab como tal
	Component* addComponent(const std::string& componentName, luabridge::LuaRef param);

	template<typename T>
	T* getComponent()
	{
		std::string name = T::GetName();
		auto it = cmpMap_.find(name);
		if (it != cmpMap_.end())
			return (T*)cmpMap_[name];
		return nullptr;
	}

	Transform* transform() {
		return transform_;
	}


	inline bool hasComponent(const std::string& name);

	inline bool isActive() const {
		return active_;
	}
	inline void setActive(bool state) {
		active_ = state;
	}
	void removeComponent(const std::string& name);

	std::string name() { return name_; }
	std::string tag() { return tag_; }
	void preUpdate();

	void update();

	void lateUpdate();

	void onCollisionEnter(QuackEntity* other);

	void onCollisionStay(QuackEntity* other);

	void onCollisionExit(QuackEntity* other);

};