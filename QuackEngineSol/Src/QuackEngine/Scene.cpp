#include "Scene.h"
#include "LuaManager.h"

Scene::Scene(const std::string& file, const std::string& name)
{
	luabridge::LuaRef refScene = readLuaFile(file, name);

	//sacamos el vector de entidades y las creamos
	enableExceptions(refScene);

	
	std::list<std::string> entidades = refScene.rawget("entities");
	std::vector<std::string> t = refScene.rawget("entities").cast<std::vector<std::string>>();

	for(std::string entityName:entidades)
	{
		//creamos todas las entidades
		QuackEntity* entity = new QuackEntity();
		
		//buscar el archivo de esta entidad y cargar sus componentes
		std::string path = "lua/Entities/" + entityName + ".lua";
		luabridge::LuaRef refEntity = readLuaFile(path, entityName);
		std::vector<std::string> components = refScene.rawget("components");

		//creamos todos los componentes y se los añadimos a las entidades
		for(std::string compName: components)
		{			
			entity->addComponent(compName);
		}
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
