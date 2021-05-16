#include "MeshRenderer.h"
#include "QuackEntity.h"
#include "OgreQuack.h"
#include <Ogre.h>

using OgrePrefab = Ogre::SceneManager::PrefabType;

MeshRenderer::MeshRenderer(QuackEntity* e) : Component(e), ogreEnt_(nullptr)
{
	mSM_ = OgreQuack::Instance()->getSceneManager();
}


MeshRenderer::~MeshRenderer()
{
	//borrar basura creada al meter la mesh?� como el Ogre::Entity quizas no lo s�
}


void MeshRenderer::onEnable()
{
	if (firstEnable_) {
		node_ = transform->getNode();
		if (ogreEnt_)
			node_->attachObject(ogreEnt_);
		firstEnable_ = false;
	}
	if (ogreEnt_)
		ogreEnt_->setVisible(visible_);
}

void MeshRenderer::onDisable()
{
	ogreEnt_->setVisible(false);
}



bool MeshRenderer::init(luabridge::LuaRef parameterTable)
{
	std::string mesh = readVariable<std::string>(parameterTable, "Mesh");

	if (mesh == "Sphere")
		ogreEnt_ = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE);
	else if (mesh == "Cube")
		ogreEnt_ = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_CUBE);
	else if (mesh == "Plane")
		ogreEnt_ = mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);
	else try {
		ogreEnt_ = mSM_->createEntity(mesh);
	}
	catch (std::exception& e) {
		std::cout << "ERROR: no existe la malla " << mesh << '\n';
	}

	materialName_ = readVariable<std::string>(parameterTable, "Material");
	if (materialName_ != "")
		setMaterial(materialName_);

	//visible_ = lo que venga de LUA;								TO DO , PASAR POR LUA SI ES VISIBLE O NO

	return true;
}

void MeshRenderer::setMeshByPrefab(PrefabType prefab) {
	OgrePrefab p = (OgrePrefab)prefab;
	entity_->transform()->getNode()->detachAllObjects();
	ogreEnt_ = mSM_->createEntity(p);
	ogreEnt_->setVisible(visible_);
	node_->attachObject(ogreEnt_);
}

void MeshRenderer::setMeshByName(const std::string& name) {
	entity_->transform()->getNode()->detachAllObjects();
	ogreEnt_ = mSM_->createEntity(name);
	ogreEnt_->setVisible(visible_);
	node_->attachObject(ogreEnt_);
}

Ogre::Mesh* MeshRenderer::getMesh() const
{
	return ogreEnt_->getMesh().get();
}

void MeshRenderer::setVisible(bool visible)
{
	visible_ = visible;
	ogreEnt_->setVisible(visible_);
}

void MeshRenderer::setMaterial(std::string materialName)
{
	ogreEnt_->setMaterialName(materialName);
	ogreEnt_->setCastShadows(true);
}

