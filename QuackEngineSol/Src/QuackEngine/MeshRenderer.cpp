#include "MeshRenderer.h"
#include "OgreQuack.h"
#include "QuackEntity.h"
#include <Ogre.h>

using OgrePrefab = Ogre::SceneManager::PrefabType;

MeshRenderer::MeshRenderer(QuackEntity* e) : Component(e)
{
}


MeshRenderer::~MeshRenderer()
{
	//borrar basura creada al meter la mesh?¿ como el Ogre::Entity quizas no lo sé
}

bool MeshRenderer::init(luabridge::LuaRef parameterTable)
{
	if(parameterTable.state())
		enableExceptions(parameterTable);
	entity_->getOgreEntity()->setVisible(true);
	return true;
}

void MeshRenderer::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	Ogre::Entity* ent = entity_->getSceneManager()->createEntity(p);
	entity_->setOgreEntity(ent);

}

void MeshRenderer::setMeshByName(const std::string& name) {

}

Ogre::Mesh* MeshRenderer::getMesh() const
{
	return entity_->getOgreEntity()->getMesh().get();
}

void MeshRenderer::setVisible(bool visible)
{
	entity_->getOgreEntity()->setVisible(visible);
}


