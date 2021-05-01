#include "QuackEntity.h"
#include "OgreQuack.h"
#include "FactoryManager.h"
#include "LuaManager.h"
#include <Ogre.h>
#include "checkML.h"


QuackEntity::QuackEntity(std::string name, bool active, std::string tag) : active_(active), name_(name), tag_(tag)
{
}

QuackEntity::~QuackEntity() {
	for (auto c : components_) {
		delete c;
		c = nullptr;
	}
}

Component* QuackEntity::addComponent(const std::string& componentName, LuaRef param)
{
	if (hasComponent(componentName)) //para no repetir componentes
		return cmpMap_[componentName];
	else {
		std::cout << "Cargando el componente: " << componentName << "\n";
		Component* c = FactoryManager::instance()->create(componentName);
		c->setEntity(this);
		if (param.isNil()) std::cout << "ERROR: no se ha podido cargar los valores del componente " << componentName << "\n";
		else c->init(param);
		components_.push_back(c);

		cmpMap_.emplace(componentName, c);
		cmpMap_[componentName] = c; //sin esta linea, el map guarda null por alg�n motivo

		return c;
	}
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

void QuackEntity::preUpdate()
{
	for (Component* c : components_)
		c->preUpdate();
}

void QuackEntity::update()
{
	for (Component* c : components_)
		c->update();
}

void QuackEntity::lateUpdate()
{
	for (Component* c : components_)
		c->lateUpdate();
}

void QuackEntity::onCollisionEnter(QuackEntity* other , Vector3D point)
{
	for (Component* c : components_)
		c->onCollisionEnter(other, point);
}

void QuackEntity::onCollisionStay(QuackEntity* other , Vector3D point)
{
	for (Component* c : components_)
		c->onCollisionStay(other, point);
}

void QuackEntity::onCollisionExit(QuackEntity* other , Vector3D point)
{
	for (Component* c : components_)
		c->onCollisionExit(other, point);
}