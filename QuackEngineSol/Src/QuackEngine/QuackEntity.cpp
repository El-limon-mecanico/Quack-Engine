#include "QuackEntity.h"
#include "LuaManager.h"
#include "OgreQuack.h"
#include <Ogre.h>

QuackEntity::QuackEntity(bool active, std::string tag) : active_(active), tag_(tag)
{
	Ogre::SceneManager* mSM = OgreQuack::Instance()->getSceneManager();
	node_ = mSM->getRootSceneNode()->createChildSceneNode();
}

QuackEntity::~QuackEntity() {
	for (auto c : components_) {
		delete c;
		c = nullptr;
	}
}

Component* QuackEntity::addComponent(const std::string& name)
{
	if (hasComponent(name))
		return cmpMap_[name];
	else {
		Component* c = FactoryManager::instance()->create(name);
		c->setEntity(this);
		c->init(readLuaFile(("lua/Components/"+name+".lua"),name));
		components_.push_back(c);
		cmpMap_.insert({ name , c });
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

//al igual por comodidad viene bien tener este método, pero realmente no es algo necesario y puede hacerse fuera de esto
void QuackEntity::setParent(Ogre::SceneNode* parent)
{
	parent->addChild((Node*)node_); //no se si esto es correcto alsjdhajlsdhalj no he testeado
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