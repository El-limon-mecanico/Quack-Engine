#include "Scene.h"
#include "CEGUIQuack.h"
#include "LuaManager.h"
#include "CallBacks.h"
#include "SoundQuack.h"

Scene::Scene(const std::string& file, const std::string& name) {
	std::cout << "Cargando escena " << name << "\n";

	//los call backs de los botones se tienen que crear antes de que se empiecen a cargar las entidades
	CallBacks::instance()->addMethod("botonPresionado", callBackBoton);
	lua_State* state = nullptr;
	try {
		state = readFileLua(file);
		std::cout << "Archivo " << file << " abierto correctamente\n";
	}
	catch (std::string& error) {
		std::cout << "ERROR: no se pudo leer el archivo " << file << "\n";
		std::cout << error << '\n';
		return;
	}
	if (state == nullptr) {
		std::cout << "ERROR: no se pudo leer el archivo " << file << "\n";
		return;
	}

	LuaRef refScene = NULL;
	try {
		refScene = readElementFromFile(state, name);
	}
	catch (...) {
		std::cout << "ERROR: no se pudo cargar la escena del archivo " << file << "\n";
		return;
	}

	//sacamos el vector de entidades y las creamos
	enableExceptions(refScene);

	LuaRef entidades = NULL;
	try {
		//leemos el vector que contiene las entidades
		entidades = refScene.rawget("entities");
	}
	catch (...) {
		std::cout << "ERROR: no se pudo cargar la lista de entidades de la escena " << file << "\n";
		return;
	}

	for (int i = 1; i <= entidades.length(); i++)
	{
		std::string ent = entidades[i];
		std::cout << "Cargando " << ent << "\n";

		//crea las entidades con sus compoenntes
		//con el nombre ent, se busca el .lua y se cree lo que pone alli
		LuaRef entInfo = readElementFromFile(state, ent);

		if (!createEntity(ent, entInfo)) std::cout << "ERROR: no se ha podido cargar la entidad: " << ent;
		std::cout << "\n";
	}
	std::cout << "Listo.\n\n-------------------------\n\n";
}

QuackEntity* Scene::createEntity(const std::string& entityName, LuaRef entInfo)
{
	QuackEntity* entity = new QuackEntity(entityName);

	std::cout << "Creando entidad " << entityName << "\n";

	if (entInfo == NULL || entInfo.isNil() || entInfo.isRefNil()) {
		std::cout << "ERROR: No se encontro la informacion de la entidad\n";
		return nullptr;
	}

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

	std::cout << "\n	Fin de la lectura de componentes.\n";
	bool active = true;
	bool correct = readVariable<bool>(entInfo, "Active", &active);
	if (correct) entity->setActive(active);

	std::string tag = "Default";
	correct = readVariable<std::string>(entInfo, "Tag", &tag);
	if (correct)
		entity->setTag(tag);

	addEntity(entity);

	return entity;
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
		if (sceneStarted)
			if (e->isActive())
				e->start();
	}
}

QuackEntity* Scene::createEntityByPrefab(const std::string& file, const std::string& nameInFile, const std::string& nameInGame)
{
	std::cout << "\n\n";

	lua_State* state = nullptr;
	try {
		state = readFileLua(file);
		std::cout << "Archivo " << file << " abierto correctamente\n";
	}
	catch (std::string& error) {
		std::cout << "ERROR: no se pudo leer el archivo " << file << "\n";
		std::cout << error << '\n';
		return nullptr;
	}
	if (state == nullptr) {
		std::cout << "ERROR: no se pudo leer el archivo " << file << "\n";
		return nullptr;
	}

	LuaRef refEntity = NULL;
	try {
		refEntity = readElementFromFile(state, nameInFile);
	}
	catch (...) {
		std::cout << "ERROR: no se pudo cargar la entidad del archivo " << file << "\n";
		return nullptr;
	}
	std::cout << "Cargando " << nameInFile << "\n";

	QuackEntity* entity;
	enableExceptions(refEntity);

	entity = createEntity(nameInGame, refEntity);
	if (!entity)
		std::cout << "ERROR: no se ha podido cargar la entidad: " << nameInFile;

	std::cout << "\n\n";
	return entity;
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

void Scene::setSceneActive(bool set)
{
	for (QuackEntity* qEnt : entities_)
		qEnt->setActive(set);
}

void Scene::callBackBoton()
{
	std::cout << "Se ha presionado el boton\n";
}
