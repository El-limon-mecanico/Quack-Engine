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

namespace CEGUI
{
	class Window;
}


class QUACK_ENGINE_PRO_API Scene
{
private:
	std::vector<QuackEntity*> entities_;

	QuackEntity* createEntity(const std::string& fileName, luabridge::LuaRef entInfo);

	void clearEntities();

	bool sceneStarted = false;

public:
	Scene(const std::string& file, const std::string& name);
	~Scene();

	void addEntity(QuackEntity* e); 

	QuackEntity* createEntityByPrefab(const std::string& file, const std::string& name);

	void start();

	void preUpdate();

	void physicsUpdate();

	void fixedUpdate();

	void update();

	void lateUpdate();

	void lastUpdate();

	/// <summary>
	/// Busca y devuelve el primer objeto en la escena con ese nombre
	/// </summary>
	/// <param name="name">Nombre del objeto a buscar</param>
	/// <returns>Primer objeto en la escena con ese nombre</returns>
	QuackEntity* getObjectWithName(std::string name);

	/// <summary>
	/// Busca y devuelve una lista con los objetos con el nombre indicado
	/// </summary>
	/// <param name="name">Nombre de los objetos a buscar</param>
	/// <returns>Lista de objetos con ese nombre en la escena</returns>
	std::vector<QuackEntity*> getAllObjectsWithName(std::string name);

	static void callBackBoton();

};
