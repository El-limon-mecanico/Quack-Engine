#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
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

	//el component name es el nombre del componente como tal (mismo nombre para varias entidades con el mismo componente)
	Component* addComponent(const std::string& componentName, luabridge::LuaRef param);

	template<typename T>
	T* getComponent()
	{
		std::string componentName = T::GetName();
		auto it = cmpMap_.find(componentName);
		if (it != cmpMap_.end())
			return (T*)cmpMap_[componentName];
		return nullptr;
	}

	template <typename T>
	inline bool hasComponent() {
		return cmpMap_[T::GetName()];
	}

	inline bool hasComponent(const std::string& componentName) {
		return cmpMap_[componentName];
	}

	inline bool isActive() const {
		return active_;
	}
	inline void setActive(bool state) {
		active_ = state;
	}

	void removeComponent(const std::string& componentName);

	template<typename T>
	void removeComponent()
	{
		std::string name = T::GetName();

		if (!hasComponent(name))
			return;

		Component* c = cmpMap_[name];
		for (auto it = components_.begin(); it != components_.end(); it++) {
			if ((*it) == c) {
				components_.erase(it);
				break;
			}
		}

		delete cmpMap_[name];
		cmpMap_[name] = nullptr;
	};

	std::string name() { return name_; }
	std::string tag() { return tag_; }
	void preUpdate();

	void update();

	void lateUpdate();

	void onCollisionEnter(QuackEntity* other , Vector3D point);

	void onCollisionStay(QuackEntity* other , Vector3D point);

	void onCollisionExit(QuackEntity* other , Vector3D point);

};