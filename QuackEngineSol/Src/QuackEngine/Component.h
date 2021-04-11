#pragma once
#include <iostream>
#include <unordered_map>
#include "LuaBridgeTest.h"

class Entity;

class Component {
protected:
	Entity* entity_;

public:
	Component(Entity* e = nullptr) :
		entity_(e) {
	}

	virtual ~Component() {}

	inline void setEntity(Entity* e) {
		entity_ = e;
	}

	inline Entity* getEntity() {
		return entity_;
	}

	//TODO cambiar a una tabla de lua
	virtual bool init(const std::unordered_map<std::string, luabridge::LuaRef>& parameterTable) = 0;
	virtual void update() {}
	virtual void render() {}
};