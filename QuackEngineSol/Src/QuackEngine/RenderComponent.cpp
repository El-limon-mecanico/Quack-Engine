#include "RenderComponent.h"
#include "QuackEnginePro.h" //---->Habria que hacer las modificaciones necesarias para acceder a Ogre a raíz de los cambios en el Singleton hechos recientemente
#include "OgreQuack.h"

RenderComponent::RenderComponent(QuackEntity* e) : Component(e)
{

}

RenderComponent::~RenderComponent()
{
}

bool RenderComponent::init(luabridge::LuaRef parameterTable)
{
	enableExceptions(parameterTable);

	return true;
}

void RenderComponent::setParent(Ogre::SceneNode* parent)
{
	parent->addChild((Node*)node_); //no se si esto es correcto alsjdhajlsdhalj no he testeado
}


