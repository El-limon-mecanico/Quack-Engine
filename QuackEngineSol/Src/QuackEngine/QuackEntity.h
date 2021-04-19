#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
#include "FactoryManager.h"
#include <unordered_map>

class QuackEntity {

protected:

private:
	bool active_;
	std::vector<Component*> components_;
	std::string tag_;
	std::unordered_map<std::string, Component*> cmpMap_;

public:
	QuackEntity(bool active = true , std::string tag = "Default"): active_(active) , tag_(tag){}
	~QuackEntity();

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
	void update();
};