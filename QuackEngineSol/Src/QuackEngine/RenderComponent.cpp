#include "RenderComponent.h"
#include "OgreQuack.h"
#include "QuackEntity.h"
#include <Ogre.h>

using OgrePrefab = Ogre::SceneManager::PrefabType;

RenderComponent::RenderComponent(QuackEntity* e) : Component(e)
{

}

RenderComponent::~RenderComponent()
{
	//borrar basura creada al meter la mesh?¿ como el Ogre::Entity quizas no lo sé
}

bool RenderComponent::init(luabridge::LuaRef parameterTable)
{
	enableExceptions(parameterTable);
	//ESTO HAY QUE CAMBIARLO A ACCESO POR SINGLETON---> OgreQuack::instance()->etc
	//Además, no sé si hay que meter algo de Lua, la inicialización de la Mesh si tuviese, o de la cámara, o de la luz
	mSM_ = OgreQuack::Instance()->getSceneManager();
	return true;
}

void RenderComponent::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	Ogre::Entity* e = mSM_->createEntity(p);
	entity_->getNode()->attachObject(e);
}

void RenderComponent::setMeshByName(const std::string& name) {

}


