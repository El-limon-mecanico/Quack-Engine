#include "Scene.h"
#include "LuaManager.h"

Scene::Scene(const std::string& file, const std::string& name)
{
	lua_State* state = readFileLua(file);
	LuaRef refScene = readElementFromFile(state, name);

	//sacamos el vector de entidades y las creamos
	enableExceptions(refScene);

	//leemos el vector que contiene las entidades
	LuaRef entidades = refScene.rawget("entities");

	for(int i=1;i<= entidades.length();i++)
	{
		std::string ent = entidades[i];
		std::cout << "Cargando " << ent << "\n";

		//crea las entidades con sus compoenntes
		//con el nombre ent, se busca el .lua y se cree lo que pone alli
		createEntity(ent);
	}
	
	
}

void Scene::createEntity(const std::string& fileName)
{
	std::string path = "Entities/" + fileName + ".lua";
	
	//primero leemos 
	
}

Scene::~Scene()
{
}

void Scene::update()
{
	std::cout << "New frame\n";
	for(QuackEntity* entity:entities_)
	{
		entity->update();
	}
}
