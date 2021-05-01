#include "Transform.h"
#include "QuackEntity.h"
#include <Ogre.h>
#include "OgreQuack.h"

Transform::Transform(Vector3D pos, Vector3D rot, Vector3D scale): position(pos), rotation(rot), scale(scale)
{
	node_ = OgreQuack::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	setParent(trRoot_.get());
}
Transform::Transform(Ogre::SceneNode* n) : position(), rotation(), scale(1,1,1) {
	node_ = n;
	setParent(this);
}
bool Transform::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	position = Vector3D(pos[1], pos[2], pos[3]);
	LuaRef rot = readVariable<LuaRef>(parameterTable, "Rotation");
	rotation = Vector3D(rot[1], rot[2], rot[3]);
	LuaRef scl = readVariable<LuaRef>(parameterTable, "Scale");
	scale = Vector3D(scl[1], scl[2], scl[3]);

	//TODO: HAY QUE METER LOS HIJOS POR LUA

	return true;
}

std::unique_ptr<Transform>  Transform::trRoot_;

Transform* Transform::InitRoot()
{
	assert(trRoot_.get() == nullptr);
	trRoot_.reset(new Transform(OgreQuack::Instance()->getSceneManager()->getRootSceneNode()));
	return trRoot_.get();
}

Transform* Transform::RootTransform()
{
	assert(trRoot_.get() != nullptr);
	return trRoot_.get();
}

void Transform::cleanChildren()
{
	for (Transform* c : children_)
		c->parent_ = nullptr;
	children_.clear();
}

inline QuackEntity* Transform::getChildByTag(std::string tag) const
{
	int i = 0;
	while (i < childrenCount()) {
		if (tag == children_[i]->entity_->tag())
			return children_[i]->entity_;
	}
	return nullptr;
}
inline QuackEntity* Transform::getChildByName(std::string name) const
{
	int i = 0;
	while (i < childrenCount()) {
		if (name == children_[i]->entity_->name())
			return children_[i]->entity_;
	}
	return nullptr;
}

Ogre::SceneNode* Transform::getNode()
{
	return node_;
}


void Transform::physicsUpdate()
{
	position = Vector3D::fromOgre(node_->getPosition());

	std::cout << position.x() << " " << position.y() << " " << position.z() << "\n";
}

void Transform::lateUpdate()
{
	node_->setPosition(position.toOgre());
}

void Transform::Translate(Vector3D t, bool global)
{

}
void Transform::Rotate(Vector3D r, bool global)
{

}
void Transform::Scale(Vector3D s, bool global)
{

}