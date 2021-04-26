#include "QuackEntity.h"
#include "OgreQuack.h"
#include <Ogre.h>

QuackEntity::QuackEntity(bool active, std::string tag) : active_(active), tag_(tag)
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
		cmpMap_.insert({ componentName , c });
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

void QuackEntity::update()
{
	for (Component* c : components_)
		c->update();
}

inline bool QuackEntity::hasComponent(const std::string& name)
{
	return cmpMap_[name];
}

Component* QuackEntity::getComponent(const std::string& name)
{
	if (cmpMap_[name])
		return cmpMap_[name];
	return nullptr;
}



//Comentamos el Update y Render de Samir porque lo haremos diferente pero ykse
	/*void Entity::update() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->update();
		}
	}

	void Entity::render() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->render();
		}
	}*/