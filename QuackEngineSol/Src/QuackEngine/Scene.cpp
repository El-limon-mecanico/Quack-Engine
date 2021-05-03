#include "Scene.h"
#include "LuaManager.h"

Scene::Scene(const std::string& file, const std::string& name)
{
	lua_State* state = readFileLua(file);
	LuaRef refScene = readElementFromFile(state, name);
	int aaa = refScene.length();
	//sacamos el vector de entidades y las creamos
	enableExceptions(refScene);

	//leemos el vector que contiene las entidades
	LuaRef entidades = refScene.rawget("entities");

	for (int i = 1; i <= entidades.length(); i++)
	{
		std::string ent = entidades[i];
		std::cout << "Cargando " << ent << "\n";

		//crea las entidades con sus compoenntes
		//con el nombre ent, se busca el .lua y se cree lo que pone alli
		LuaRef entInfo = readElementFromFile(state, ent);
		if (!createEntity(ent, entInfo)) std::cout << "ERROR: no se ha podidio cargar la entidad: " << ent;
	}
}

bool Scene::createEntity(const std::string& fileName, LuaRef entInfo)
{
	QuackEntity* entity = new QuackEntity(fileName);

	//leemos el array de componentes
	LuaRef components = entInfo.rawget("Components");
	//comprobacion de errores
	if (components.isNil()) { std::cout << "ERROR: No se ha podido leer el Array 'Components' \n"; return false; }

	for (int i = 1; i <= components.length(); i++)
	{
		//carga los componentes
		enableExceptions(components[i]);
		entity->addComponent(components[i], entInfo.rawget(components[i]));
	}

	entity->setActive(true);						// COMPROBAR SI ESTÁ AC

	addEntity(entity);

	return true;
}

Scene::~Scene()
{
	for (QuackEntity* qEnt : entities_) {
		delete qEnt;
		qEnt = nullptr;
	}
}

void Scene::addEntity(QuackEntity* e)
{
	if (e) {
		entities_.push_back(e);
		if (e->isActive()){}
			e->start();
	}
}

void Scene::preUpdate()
{
	for (QuackEntity* entity : entities_)
	{
		entity->preUpdate();
	}
}

void Scene::physicsUpdate()
{
	for (QuackEntity* entity : entities_)
	{
		entity->physicsUpdate();
	}
}

void Scene::fixedUpdate()
{
	//std::cout << "New frame\n";
	for (QuackEntity* entity : entities_)
	{
		entity->fixedUpdate();
	}
}

void Scene::update()
{
	//std::cout << "New frame\n";
	for (QuackEntity* entity : entities_)
	{
		entity->update();
	}
}

void Scene::lateUpdate()
{
	for (QuackEntity* entity : entities_)
	{
		entity->lateUpdate();
	}
}

void Scene::lastUpdate()
{
	for (QuackEntity* entity : entities_)
	{
		entity->lastUpdate();
	}
}
