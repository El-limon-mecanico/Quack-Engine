#include "Render.h"
#include "OgreQuack.h"
#include "QuackEntity.h"
#include <Ogre.h>

using OgrePrefab = Ogre::SceneManager::PrefabType;

Render::Render(QuackEntity* e) : Component(e)
{
}


Render::~Render()
{
	//borrar basura creada al meter la mesh?¿ como el Ogre::Entity quizas no lo sé
}

bool Render::init(luabridge::LuaRef parameterTable)
{
	enableExceptions(parameterTable);
	mSM_ = OgreQuack::Instance()->getSceneManager();
	ent_ = nullptr;
	return true;
}

void Render::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	ent_ = mSM_->createEntity(p);
	entity_->getNode()->attachObject(ent_);
}

void Render::setMeshByName(const std::string& name) {

}


