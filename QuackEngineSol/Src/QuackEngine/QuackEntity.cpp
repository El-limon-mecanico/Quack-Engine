#include "QuackEntity.h"
#include "OgreQuack.h"
#include "FactoryManager.h"
#include "LuaManager.h"
#include <Ogre.h>
#include "checkML.h"


QuackEntity::QuackEntity(std::string name, bool active, std::string tag) : active_(active), name_(name), tag_(tag)
{
	transform_ = addComponent<Transform>();
}

QuackEntity::~QuackEntity() {
	for (auto c : components_) {
		delete c;
		c = nullptr;
	}
}

QuackEntity::QuackEntity(Transform* tr) :
	active_(true),
	name_("EntityRoot"),
	tag_("Root"),
	transform_(tr)
{
}

std::unique_ptr<QuackEntity>  QuackEntity::qeRoot_;

void QuackEntity::Init()
{
	assert(qeRoot_.get() == nullptr);
	qeRoot_.reset(new QuackEntity(Transform::InitRoot()));
}

QuackEntity* QuackEntity::RootEntity()
{
	assert(qeRoot_.get() != nullptr);
	return qeRoot_.get();
}

Component* QuackEntity::addComponent(const std::string& componentName, LuaRef param)
{
	if (hasComponent(componentName)) //para no repetir componentes
		return cmpMap_[componentName];
	else {
		std::cout << "Cargando el componente: " << componentName << "\n";
		Component* c = FactoryManager::instance()->create(componentName);
		c->setEntity(this);
		c->transform = transform();
		if (param.isNil()) std::cout << "ERROR: no se ha podido cargar los valores del componente " << componentName << "\n";
		else c->init(param);
		components_.push_back(c);

		cmpMap_.emplace(componentName, c);
		cmpMap_[componentName] = c; //sin esta linea, el map guarda null por alg�n motivo

		//if(componente enbale)																// TO DO GUARDAR SI EL COMPONENTE ESTÁ ENABLE
		c->onEnable();

		return c;
	}
}

Component* QuackEntity::getComponent(const std::string& componentName)
{
	auto it = cmpMap_.find(componentName);
	if (it != cmpMap_.end())
		return cmpMap_[componentName];
	return nullptr;
}

void QuackEntity::removeComponent(const std::string& componentName)
{
	if (!hasComponent(componentName))
		return;

	Component* c = cmpMap_[componentName];
	for (auto it = components_.begin(); it != components_.end(); it++) {
		if ((*it) == c) {
			components_.erase(it);
			break;
		}
	}

	delete cmpMap_[componentName];
	cmpMap_[componentName] = nullptr;
}

void QuackEntity::start()
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->start();
}

void QuackEntity::preUpdate()
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->preUpdate();
}

void QuackEntity::physicsUpdate()
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->physicsUpdate();
}

void QuackEntity::update()
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->update();
}

void QuackEntity::lateUpdate()
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->lateUpdate();
}

void QuackEntity::onCollisionEnter(QuackEntity* other, Vector3D point)
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onCollisionEnter(other, point);
}

void QuackEntity::onCollisionStay(QuackEntity* other, Vector3D point)
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onCollisionStay(other, point);
}

void QuackEntity::onCollisionExit(QuackEntity* other, Vector3D point)
{
	if (active_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onCollisionExit(other, point);
}

void QuackEntity::onEnable()
{
	for (Component* c : components_)
		if (c->isEnable())
			c->onEnable();
}

void QuackEntity::onDisable()
{
	for (Component* c : components_)
		if (c->isEnable())
			c->onDisable();
}
