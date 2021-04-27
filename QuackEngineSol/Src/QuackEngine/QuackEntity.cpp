#include "QuackEntity.h"
#include "OgreQuack.h"
#include <Ogre.h>

QuackEntity::QuackEntity(std::string name, bool active, std::string tag) : active_(active), name_(name), tag_(tag)
{
	//mSM_ = OgreQuack::Instance()->getSceneManager();
	//node_ = mSM_->getRootSceneNode()->createChildSceneNode();
	//setOgreEntity(mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_CUBE)); //CAMBIAR ESTE CUBO POR UNA MALLA EMPTY QUE TENGAMOS EN EL RESOURCES
}

QuackEntity::~QuackEntity() {
	for (auto c : components_) {
		delete c;
		c = nullptr;
	}
}

#include "Prueba.h"
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

void QuackEntity::removeComponent(const std::string& name)
{
	if (!hasComponent(name))
		return;

	Component* c = cmpMap_[name];
	for (auto it = components_.begin(); it != components_.end(); it++) {
		if ((*it) == c) {
			components_.erase(it);
			break;
		}
	}

	delete cmpMap_[name];
	cmpMap_[name] = nullptr;
}

inline bool QuackEntity::hasComponent(const std::string& name)
{
	return cmpMap_[name];
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

void QuackEntity::onCollisionEnter(QuackEntity* other)
{
	for (Component* c : components_)
		c->onCollisionEnter(other);
}

void QuackEntity::onCollisionStay(QuackEntity* other)
{
	for (Component* c : components_)
		c->onCollisionStay(other);
}

void QuackEntity::onCollisionExit(QuackEntity* other)
{
	for (Component* c : components_)
		c->onCollisionExit(other);
}