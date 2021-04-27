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
	mSM_ = OgreQuack::Instance()->getSceneManager();
	node_ = mSM_->getRootSceneNode()->createChildSceneNode();

	std::string type;
	readVariable<std::string>(parameterTable, "Type", type);

	if (type == "Sphere")
		setOgreEntity(mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE));
	else if (type == "Cube")
		setOgreEntity(mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_CUBE));
	else if (type == "Plane")
		setOgreEntity(mSM_->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE));
	else std::cout << "ERROR: no existe el tipo de prefab: " << type << "\n";

	return true;
}

void Render::setOgreEntity(Ogre::Entity* e)
{
	Ogre::Entity* aux = ogreEnt_;
	node_->detachAllObjects();
	ogreEnt_ = e;
	node_->attachObject(ogreEnt_);
	delete aux; aux = nullptr;
}

void Render::setParent(Ogre::SceneNode* parent)
{
	parent->addChild((Node*)node_); //no se si esto es correcto alsjdhajlsdhalj no he testeado
}

void Render::setMeshByName(const std::string& name) {

}


