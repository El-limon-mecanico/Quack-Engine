#include "Scene.h"
#include "LuaManager.h"

Scene::Scene(const std::string& file, const std::string& name)
{
	LuaRef refScene = readLuaFile(file, name);

	//sacamos el vector de entidades y las creamos
	enableExceptions(refScene);

	//leemos el vector que contiene las entidades
	LuaRef entidades = refScene.rawget("entities");

	for(int i=1;i<= entidades.length();i++)
	{
		std::string ent = entidades[i];
		std::cout << "Cargando " << ent << "\n";

		
	}
	
}

Scene::~Scene()
{
}

void Scene::update()
{
	for(QuackEntity* entity:entities_)
	{
		entity->update();
	}
}