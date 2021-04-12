#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
#include "FactoryManager.h"
#include <unordered_map>

class Entity {

protected:

private:
	bool active_;
	std::vector<Component*> components_;
	std::string tag_;
	std::unordered_map<std::string, Component*> cmpMap_;

public:
	Entity(): active_(true){}
	virtual ~Entity();

	bool* addComponent(const std::string& name);

	//template<typename T, typename ...Ts>
	//T* addComponent(Ts&&... args) {
	//	T* c = new T(std::forward<Ts>(args)...);
	//	c->SetEntity(this);
	//	c->Init();
	//	//En principio no usaremos un archivo ECS donde guardamos un enum con los ID, pero ahora mismo no sabemos como hacerlo asi que lo copio asi tal cual xdd
	//	constexpr auto id = ecs::cmpIdx<T>;

	//	if (cmpArray_[id] != nullptr) {
	//		RemoveComponent<T>();
	//	}

	//	cmpArray_[id] = c;
	//	components_.emplace_back(c);

	//	return c;
	//}
	
	/*template<typename T>
	void removeComponent() {
		auto id = ecs::cmpIdx<T>; //lo mismo que antes con el ID
		if (cmpArray_[id] != nullptr) {
			Component* old_cmp = cmpArray_[id];
			cmpArray_[id] = nullptr;
			components_.erase( //
			std::find_if( //
				components_.begin(), //
				components_.end(), //
				[old_cmp](const Component* c) { //
					return c == old_cmp;
				}));
			delete old_cmp;
		}
	}*/

	/*template<typename T>
	inline T* getComponent() {
		auto id = ecs::cmpIdx<T>;
		return static_cast<T*>(cmpArray_[id]);
	}*/

	/*template<typename T>
	inline bool hasComponent() {
		auto id = ecs::cmpIdx<T>;
		return cmpArray_[id] != nullptr;
	}*/

	inline bool isActive() const {
		return active_;
	}
	inline void setActive(bool state) {
		active_ = state;
	}


	//void update();
	//void render();
};
