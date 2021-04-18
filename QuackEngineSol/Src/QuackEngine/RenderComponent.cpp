#include "RenderComponent.h"
#include "QuackEnginePro.h" //---->Habria que hacer las modificaciones necesarias para acceder a Ogre a raíz de los cambios en el Singleton hechos recientemente
#include "OgreQuack.h" //-> ?¿ idk

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
	Ogre::SceneManager* mSM_ = QuackEnginePro::instance()->getOgreQuack()->getSceneManager();
	node_ = mSM_->getRootSceneNode()->createChildSceneNode();

	return true;
}

//al igual por comodidad viene bien tener este método, pero realmente no es algo necesario y puede hacerse fuera de esto
void RenderComponent::setParent(Ogre::SceneNode* parent)
{
	parent->addChild((Node*)node_); //no se si esto es correcto alsjdhajlsdhalj no he testeado
}

void RenderComponent::setMeshByPrefab(Ogre::SceneManager::PrefabType prefab) {
	Ogre::Entity* e = mSM_->createEntity(prefab);
	node_->attachObject(e);
}

void RenderComponent::setMeshByName(const std::string& name) {

}

