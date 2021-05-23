#include "QuackEntity.h"
#include "OgreQuack.h"
#include "FactoryManager.h"
#include "LuaManager.h"
#include <Ogre.h>
#include "checkML.h"


QuackEntity::QuackEntity(std::string name, bool active, std::string tag) : enable_(active), name_(name), tag_(tag)
{
	transform_ = addComponent<Transform>();
}

QuackEntity::~QuackEntity() {
	for (int i = 1; i < components_.size(); i++) {
		delete components_[i];
		components_[i] = nullptr;
	}
	delete components_[0];
	components_.clear();
}

QuackEntity::QuackEntity(Transform* tr) :
	enable_(true),
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
	std::cout << "Cargando el componente: " << componentName << "\n";
	if (componentName == "Transform") {
		transform_->init(param);
		transform_->transform = transform_;
		return transform_;
	}
	else if (hasComponent(componentName)) //para no repetir componentes
		return cmpMap_[componentName];
	else {
		Component* c;
		try {
			c = FactoryManager::instance()->create(componentName);
		}
		catch (std::string& err) {
			std::cout << err;
			return nullptr;
		}
		c->setEntity(this);
		c->transform = transform();
		if (param.isNil()) std::cout << "ERROR: no se ha podido cargar los valores del componente " << componentName << "\n";
		else {
			c->init(param);
			if(!readVariable<bool>(param, "Enabled", &(c->enable))) std::cout << "ERROR: no se ha podido activar/desactivar la entidad\n";
		}
		components_.push_back(c);

		cmpMap_.insert({ componentName , c });
		cmpMap_[componentName] = c; //sin esta linea, el map guarda null por algun motivo

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
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->start();
}

void QuackEntity::preUpdate()
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->preUpdate();
}

void QuackEntity::physicsUpdate()
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->physicsUpdate();
}

void QuackEntity::fixedUpdate()
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->fixedUpdate();
}

void QuackEntity::update()
{
	if (enable_)
		for (Component* c : components_)
			if (c->isEnable())
				c->update();
}

void QuackEntity::lateUpdate()
{
	if (enable_)
		for (Component* c : components_)
			if (c->isEnable())
				c->lateUpdate();
}

void QuackEntity::lastUpdate()
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->lastUpdate();
}

void QuackEntity::onCollisionEnter(QuackEntity* other, Vector3D point, Vector3D normal)
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onCollisionEnter(other, point, normal);
}

void QuackEntity::onCollisionStay(QuackEntity* other, Vector3D point)
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onCollisionStay(other, point);
}

void QuackEntity::onCollisionExit(QuackEntity* other, Vector3D point)
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onCollisionExit(other, point);
}

void QuackEntity::onTriggerEnter(QuackEntity* other, Vector3D point)
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onTriggerEnter(other, point);
}

void QuackEntity::onTriggerStay(QuackEntity* other, Vector3D point)
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onTriggerStay(other, point);
}

void QuackEntity::onTriggerExit(QuackEntity* other, Vector3D point)
{
	if (enable_ && !destroy_)
		for (Component* c : components_)
			if (c->isEnable())
				c->onTriggerExit(other, point);
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
