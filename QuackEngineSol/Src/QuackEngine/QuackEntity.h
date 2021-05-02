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
	//Root
	QuackEntity(Transform* tr);
	static std::unique_ptr<QuackEntity> qeRoot_;					

	bool active_;
	std::vector<Component*> components_;
	std::string tag_;
	std::string name_;
	std::unordered_map<std::string, Component*> cmpMap_;
	Transform* transform_;

public:
	QuackEntity(std::string name = "DefaultName", bool active = true, std::string tag = "Default");
	~QuackEntity();

	static void Init();

	QuackEntity* RootEntity();

	std::string& name() {	return name_;	 }
	std::string& tag() {		return tag_;	 }
	inline bool isActive() const {		return active_;		}
	inline void setActive(bool state) {		
		active_ = state;
		if (active_)
			onEnable();
		else
			onDisable();
	}

	//el component name es el nombre del componente como tal (mismo nombre para varias entidades con el mismo componente)
	Component* addComponent(const std::string& componentName, luabridge::LuaRef param);
	template<typename T, typename ... Targs>
	T* addComponent(Targs&&...mArgs);

	template<typename T>
	T* getComponent();
	Component* getComponent(const std::string& componentName);

	template <typename T>
	inline bool hasComponent();
	inline bool hasComponent(const std::string& componentName) {
		return cmpMap_[componentName] != nullptr;
	}

	Transform* transform() {
		return transform_;
	}
	template<typename T>
	void removeComponent();
	void removeComponent(const std::string& componentName);

	void start();

	void preUpdate();

	void physicsUpdate();

	void fixedUpdate();

	void update();

	void lateUpdate();

	void onCollisionEnter(QuackEntity* other , Vector3D point);

	void onCollisionStay(QuackEntity* other , Vector3D point);

	void onCollisionExit(QuackEntity* other , Vector3D point);

	void onEnable();

	void onDisable();
};

template<typename T>
T* QuackEntity::getComponent() {
	return (T*)getComponent(T::GetName());
}

template <typename T>
inline bool QuackEntity::hasComponent() {
	return hasComponent(T::GetName());
}

template<typename T>
void QuackEntity::removeComponent() {
	return removeComponent(T::GetName());
}

template<typename T, typename ... Targs>
T* QuackEntity::addComponent(Targs&&...mArgs)
{
	T* c = new T(std::forward<Targs>(mArgs)...);
	c->setEntity(this);
	c->transform = transform();
	components_.push_back(c);
	cmpMap_.insert({ T::GetName() , c });
	c->onEnable();
	return c;
}