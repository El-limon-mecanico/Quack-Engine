#pragma once
#include <string>
#include <vector>
#include "QuackEntity.h"

namespace luabridge {
	class LuaRef;
}


class Scene
{
private:
	std::vector<QuackEntity*> entities_;

	bool createEntity(const std::string& fileName, luabridge::LuaRef entInfo);

public:
	Scene(const std::string& file, const std::string& name);
	~Scene();

	void addEntity(QuackEntity* e); 

	void preUpdate();

	void physicsUpdate();

	void fixedUpdate();

	void update();

	void lateUpdate();

};
