#pragma once
#include <iostream>
#include <unordered_map>
#include "LuaManager.h"
#include "Vector3D.h"

namespace luabridge {
	class LuaRef;
}

class QuackEntity;
class Transform;

class Component {
protected:
	QuackEntity* entity_;
	bool enable = true;
public:

	Component(QuackEntity* e = nullptr) :
		entity_(e) {
	}

	Transform* transform;

	virtual ~Component() {}

	inline bool isEnable() { return enable; }

	inline void setEnable(bool set) {
		enable = set;

		if (set)
			onEnable();
		else
			onDisable();
	}

	inline void setEntity(QuackEntity* e) {
		entity_ = e;
	}

	inline QuackEntity* getEntity() {
		return entity_;
	}


	// static std::string GetName() = 0 ;   HAY QUE REDEFINIRLO EN CADA COMPONENTE , SI NO NO FUNCIONA

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) = 0;

	virtual void start() {}

	virtual void preUpdate() {}

	virtual void physicsUpdate() {}

	virtual void update() {}

	virtual void lateUpdate() {}

	virtual void onCollisionEnter(QuackEntity* other, Vector3D point) {}

	virtual void onCollisionStay(QuackEntity* other, Vector3D point) {}

	virtual void onCollisionExit(QuackEntity* other, Vector3D point) {}

	virtual void onEnable() {}

	virtual void onDisable() {}
};