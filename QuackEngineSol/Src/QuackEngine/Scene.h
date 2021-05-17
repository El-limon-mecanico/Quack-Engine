#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <string>
#include <vector>
#include "QuackEntity.h"

namespace luabridge {
	class LuaRef;
}


class QUACK_ENGINE_PRO_API Scene
{
private:
	std::vector<QuackEntity*> entities_;

	bool createEntity(const std::string& fileName, luabridge::LuaRef entInfo);

	bool createUI(luabridge::LuaRef info);

	void clearEntities();

	bool sceneStarted = false;

public:
	Scene(const std::string& file, const std::string& name);
	~Scene();

	void addEntity(QuackEntity* e); 

	void start();

	void preUpdate();

	void physicsUpdate();

	void fixedUpdate();

	void update();

	void lateUpdate();

	void lastUpdate();

	static void callBackBoton();

};
