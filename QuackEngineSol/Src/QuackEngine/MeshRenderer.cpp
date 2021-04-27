#include "MeshRenderer.h"
#include "QuackEntity.h"
#include "OgreQuack.h"
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
	mSM_ = OgreQuack::Instance()->getSceneManager();
	node_ = mSM_->getRootSceneNode()->createChildSceneNode();

	std::string type = readVariable<std::string>(parameterTable, "Type");

	if (type == "Sphere")
		setOgreEntity(mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE));
	else if (type == "Cube")
		setOgreEntity(mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_CUBE));
	else if (type == "Plane")
		setOgreEntity(mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE));
	else std::cout << "ERROR: no existe el tipo de prefab: " << type << "\n";

	ogreEnt_->setVisible(true);
	return true;
}

void MeshRenderer::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	ogreEnt_ = mSM_->createEntity(p);
}

void MeshRenderer::setMeshByName(const std::string& name) {

}

Ogre::Mesh* MeshRenderer::getMesh() const
{
	return ogreEnt_->getMesh().get();
}

void MeshRenderer::setVisible(bool visible)
{
	ogreEnt_->setVisible(visible);
}