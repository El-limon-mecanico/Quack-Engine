#pragma once
#include <iostream>
#include <unordered_map>
#include <LuaBridge.h>

class QuackEntity;

class Component {
protected:
	QuackEntity* entity_;

public:
	Component(QuackEntity* e = nullptr) :
		entity_(e) {
	}
	virtual ~Component() {}

	inline void setEntity(QuackEntity* e) {
		entity_ = e;
	}

	inline QuackEntity* getEntity() {
		return entity_;
	}

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) = 0;

	virtual void preUpdate() {}

	virtual void update() {}

	virtual void lateUpdate() {}

	virtual void onCollisionEnter(QuackEntity* other) {}

	virtual void onCollisionStay(QuackEntity* other) {}

	virtual void onCollisionExit(QuackEntity* other) {}

};