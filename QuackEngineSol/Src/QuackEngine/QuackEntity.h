#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Transform.h"
#include <unordered_map>
#include "Component.h"
//#include "HasGetName.h"

namespace luabridge {
	class LuaRef;
}

namespace Ogre {
	class Root;
	class SceneManager;
	class SceneNode;
	class Entity;
}

class QUACK_ENGINE_PRO_API QuackEntity {
private:
	//Root
	QuackEntity(Transform* tr);
	static std::unique_ptr<QuackEntity> qeRoot_;

	bool enable_;
	bool destroy_ = false;
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

	std::string& name() { return name_; }
	std::string& tag() { return tag_; }
	inline bool isActive() const { return enable_; }
	inline void setActive(bool state) {
		enable_ = state;
		if (enable_)
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

	void lastUpdate();

	void onCollisionEnter(QuackEntity* other, Vector3D point, Vector3D normal);

	void onCollisionStay(QuackEntity* other, Vector3D point);

	void onCollisionExit(QuackEntity* other, Vector3D point);

	void onTriggerEnter(QuackEntity* other, Vector3D point);

	void onTriggerStay(QuackEntity* other, Vector3D point);

	void onTriggerExit(QuackEntity* other, Vector3D point);

	void onEnable();

	void onDisable();

	void destroy() { destroy_ = true; }

	bool markedForDestroy() { return destroy_; }
};

template<typename T>
T* QuackEntity::getComponent() {
	//if (HasGetName<T>::value)
		return (T*)getComponent(T::GetName());

	//PRINT_ERROR_GETNAME;
	//return nullptr;
}

template <typename T>
inline bool QuackEntity::hasComponent() {
	//if ((HasGetName<T>::value))
		return hasComponent(T::GetName());

	//PRINT_ERROR_GETNAME;
	//return nullptr;
}

template<typename T>
void QuackEntity::removeComponent() {
	//if ((HasGetName<T>::value));
		return removeComponent(T::GetName());

	//PRINT_ERROR_GETNAME;
	//return nullptr;

}

template<typename T, typename ... Targs>
T* QuackEntity::addComponent(Targs&&...mArgs)
{
	//if ((HasGetName<T>::value)) {
		//PRINT_ERROR_GETNAME;
		//return nullptr;
	//}

	T* c = new T(std::forward<Targs>(mArgs)...);
	c->setEntity(this);
	c->transform = transform();
	components_.push_back(c);
	cmpMap_.insert({ T::GetName() , c });
	c->onEnable();
	return c;
}