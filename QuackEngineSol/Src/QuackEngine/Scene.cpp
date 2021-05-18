#include "Scene.h"
#include "CEGUIQuack.h"
#include "LuaManager.h"
#include "CallBacks.h"

Scene::Scene(const std::string& file, const std::string& name)
{
	//los call backs de los botones se tienen que crear antes de que se empiecen a cargar las entidades
	CallBacks::instance()->addMethod("botonPresionado", callBackBoton);

	lua_State* state = readFileLua(file);
	LuaRef refScene = readElementFromFile(state, name);
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

		if (ent == "UI")
		{
			if (!createUI(entInfo)) std::cout << "ERROR: no se ha podidio cargar la UI de la escena:  " << name;
		}
		else
		{
			if (!createEntity(ent, entInfo)) std::cout << "ERROR: no se ha podidio cargar la entidad: " << ent;
		}
	}
}

QuackEntity* Scene::createEntity(const std::string& fileName, LuaRef entInfo)
{
	QuackEntity* entity = new QuackEntity(fileName);

	//leemos el array de componentes
	LuaRef components = entInfo.rawget("Components");
	//comprobacion de errores
	if (components.isNil()) { std::cout << "ERROR: No se ha podido leer el Array 'Components' \n"; return nullptr; }

	for (int i = 1; i <= components.length(); i++)
	{
		//carga los componentes
		enableExceptions(components[i]);
		entity->addComponent(components[i], entInfo.rawget(components[i]));
	}

	LuaRef children = entInfo.rawget("Children");
	LuaRef list = children.rawget("entities");
	

	if (!list.isNil()) {
		for (int i = 1; i <= list.length(); i++) {
			enableExceptions(list[i]);
			createEntity(list[i], children.rawget(list[i]))->transform()->setParent(entity->transform());
		}
	}

	entity->setActive(readVariable<bool>(entInfo, "Active"));

	addEntity(entity);

	return entity;
}

bool Scene::createUI(luabridge::LuaRef info)
{
	LuaRef components = info.rawget("Components");
	if (components.isNil()) { std::cout << "ERROR: No se ha podido leer el Array 'Components' \n"; return false; }


	for (int i = 1; i <= components.length(); i++)
	{
		//carga los componentes
		enableExceptions(components[i]);
		LuaRef cmpInfo = info.rawget(components[i]);

		std::string type = readVariable<std::string>(cmpInfo, "Type");
		LuaRef pos = readVariable<LuaRef>(cmpInfo, "Position");
		LuaRef size = readVariable<LuaRef>(cmpInfo, "Size");
		std::string name = readVariable<std::string>(cmpInfo, "Name");
		/*if (type == "Scheme") {
			CEGUIQuack::Instance()->loadScheme(readVariable<std::string>(cmpInfo, "Scheme"));
		}
		else if (type == "Text")
		{
			uiEntities_.push_back(CEGUIQuack::Instance()->createText(name, readVariable<std::string>(cmpInfo, "Text"),
				{ pos[1],pos[2] }, { size[1], size[2] }, readVariable<std::string>(cmpInfo, "Style")));
		}
		else if (type == "Image")
		{
			uiEntities_.push_back(CEGUIQuack::Instance()->createImage(name, readVariable<std::string>(cmpInfo, "Image"),
				{ pos[1],pos[2] }, { size[1], size[2] }, readVariable<std::string>(cmpInfo, "Style")));
		}
		else if (type == "Button")
		{
			uiEntities_.push_back(CEGUIQuack::Instance()->createButton(name, readVariable<std::string>(cmpInfo, "Text"),
				{ pos[1],pos[2] }, { size[1], size[2] }, CallBacks::instance()->getMethod(
					readVariable<std::string>(cmpInfo, "CallBackFunction")), readVariable<std::string>(cmpInfo, "Style")));
		}*/
	}
	//tan solo tenemos 3 tipos de elementos de ui


	return true;
}

Scene::~Scene()
{
	for (QuackEntity* qEnt : entities_) {
		delete qEnt;
		qEnt = nullptr;
	}

	for (CEGUI::Window* w : uiEntities_) {
		CEGUIQuack::Instance()->removeWidget(w);
		delete w;
		w = nullptr;
	}
}

void Scene::addEntity(QuackEntity* e)
{
	if (e) {
		entities_.push_back(e);
		if (sceneStarted)
			if (e->isActive())
				e->start();
	}
}

void Scene::start() {
	sceneStarted = true;
	size_t n = entities_.size();
	for (int i = 0; i < n; i++) {
		if (!entities_[i]->markedForDestroy())
			entities_[i]->start();
	}
}

void Scene::preUpdate()
{
	size_t n = entities_.size();
	for (int i = 0; i < n; i++) {
		if (!entities_[i]->markedForDestroy())
			entities_[i]->preUpdate();
	}
}

void Scene::physicsUpdate()
{
	size_t n = entities_.size();
	for (int i = 0; i < n; i++) {
		if (!entities_[i]->markedForDestroy())
			entities_[i]->physicsUpdate();
	}
}

void Scene::fixedUpdate()
{
	size_t n = entities_.size();
	for (int i = 0; i < n; i++) {
		if (!entities_[i]->markedForDestroy())
			entities_[i]->fixedUpdate();
	}
}

void Scene::update()
{
	size_t n = entities_.size();
	for (int i = 0; i < n; i++) {
		if (!entities_[i]->markedForDestroy())
			entities_[i]->update();
	}
}

void Scene::lateUpdate()
{
	size_t n = entities_.size();
	for (int i = 0; i < n; i++) {
		if (!entities_[i]->markedForDestroy())
			entities_[i]->lateUpdate();
	}
}

void Scene::lastUpdate()
{
	size_t n = entities_.size();
	for (int i = 0; i < n; i++) {
		if (!entities_[i]->markedForDestroy())
			entities_[i]->lastUpdate();
	}
	clearEntities();
}

void Scene::clearEntities()
{
	for (auto it = entities_.begin(); it != entities_.end();) {
		if ((*it)->markedForDestroy()) {
			QuackEntity* e = (*it);
			it = entities_.erase(it);
			delete e;
			e = nullptr;
		}
		else
			it++;
	}
}

QuackEntity* Scene::getObjectWithName(std::string name)
{
	for (QuackEntity* e : entities_) {
		if (e->name() == name)
			return e;
	}
	return nullptr;
}

std::vector<QuackEntity*> Scene::getAllObjectsWithName(std::string name)
{
	std::vector<QuackEntity*> eS = std::vector<QuackEntity*>();

	for (QuackEntity* e : entities_) {
		if (e->name() == name)
			eS.push_back(e);
	}

	return eS;
}

void Scene::callBackBoton()
{
	std::cout << "Se ha presionado el boton\n";
}
