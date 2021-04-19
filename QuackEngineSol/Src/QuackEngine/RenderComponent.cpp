#include "RenderComponent.h"
#include "OgreQuack.h"
#include <Ogre.h>

using OgrePrefab = Ogre::SceneManager::PrefabType;

RenderComponent::RenderComponent(QuackEntity* e) : Component(e)
{

}

RenderComponent::~RenderComponent()
{
}

bool RenderComponent::init(luabridge::LuaRef parameterTable)
{
	enableExceptions(parameterTable);
	//ESTO HAY QUE CAMBIARLO A ACCESO POR SINGLETON---> OgreQuack::instance()->etc
	//Además, no sé si hay que meter algo de Lua, la inicialización de la Mesh si tuviese, o de la cámara, o de la luz
	mSM_ = OgreQuack::Instance()->getSceneManager();
	node_ = mSM_->getRootSceneNode()->createChildSceneNode();

	return true;
}

//al igual por comodidad viene bien tener este método, pero realmente no es algo necesario y puede hacerse fuera de esto
void RenderComponent::setParent(Ogre::SceneNode* parent)
{
	parent->addChild((Node*)node_); //no se si esto es correcto alsjdhajlsdhalj no he testeado
}

void RenderComponent::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	Ogre::Entity* e = mSM_->createEntity(p);
	node_->attachObject(e);
}

void RenderComponent::setMeshByName(const std::string& name) {

}

