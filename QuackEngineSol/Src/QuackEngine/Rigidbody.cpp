#include "Rigidbody.h"
#include "BulletQuack.h"
#include "QuackEntity.h"
#include "BtOgre.h"

Rigidbody::Rigidbody(QuackEntity* e)
{
}

Rigidbody::~Rigidbody()
{
}


bool Rigidbody::init(luabridge::LuaRef parameterTable)
{
	std::string type;
	readVariable<std::string>(parameterTable, "Type", type);
	int mass;
	readVariable<int>(parameterTable, "Mass", mass);
	
	if (type == "Box") setRigidbody(mass,ColliderType::CT_BOX);
	else if (type == "Sphere")setRigidbody(mass, ColliderType::CT_SPHERE);
	else if (type == "Trimesh")setRigidbody(mass, ColliderType::CT_TRIMESH);
	else if (type == "Hull")setRigidbody(mass, ColliderType::CT_HULL);
	
	return true;
}

void Rigidbody::setRigidbody(int mass, ColliderType type)
{
	BtOgre::ColliderType t = (BtOgre::ColliderType)type;
 	Render* renderCmp = entity_->getComponent<Render>("Render");
	//Ogre::Entity* ent = ;
	rb_ = BulletQuack::Instance()->getWorld()->addRigidBody(mass, renderCmp->getOgreEntity(), t); //TODO 
}