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
	if(parameterTable.state())
		enableExceptions(parameterTable);
	return true;
}

void Render::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	Ogre::Entity* ent = entity_->getSceneManager()->createEntity(p);
	entity_->setOgreEntity(ent);

}

void Render::setMeshByName(const std::string& name) {

}


