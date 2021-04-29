#include "MeshRenderer.h"
#include "QuackEntity.h"
#include "OgreQuack.h"
#include <Ogre.h>

using OgrePrefab = Ogre::SceneManager::PrefabType;

MeshRenderer::MeshRenderer(QuackEntity* e) : Component(e)
{
	mSM_ = OgreQuack::Instance()->getSceneManager();
	node_ = mSM_->getRootSceneNode()->createChildSceneNode();
}


MeshRenderer::~MeshRenderer()
{
	//borrar basura creada al meter la mesh?� como el Ogre::Entity quizas no lo s�
}

bool MeshRenderer::init(luabridge::LuaRef parameterTable)
{
	std::string type = readVariable<std::string>(parameterTable, "Type");

	if (type == "Sphere")
		ogreEnt_ = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE);
	else if (type == "Cube")
		ogreEnt_ = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_CUBE);
	else if (type == "Plane")
		ogreEnt_ = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);
	else std::cout << "ERROR: no existe el tipo de prefab: " << type << "\n";


	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	node_->setPosition(pos[1], pos[2], pos[3]);
	
	ogreEnt_->setVisible(true);
	node_->attachObject(ogreEnt_);

	return true;
}

void MeshRenderer::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	node_->detachAllObjects();
	ogreEnt_ = mSM_->createEntity(p);
	ogreEnt_->setVisible(true);
	node_->attachObject(ogreEnt_);
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