#include "Transform.h"
#include "QuackEntity.h"
#include <Ogre.h>
#include "OgreQuack.h"


Transform::Transform(Vector3D pos, Vector3D rot, Vector3D scale) : globalPosition_(pos), rotation_(rot), scale(scale)
{
	node_ = OgreQuack::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	setParent(trRoot_.get());
}
Transform::Transform(Ogre::SceneNode* n) : globalPosition_(), rotation_(), scale(1, 1, 1) {
	node_ = n;
	setParent(this);
}
bool Transform::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	setGlobalPosition(Vector3D(pos[1], pos[2], pos[3]));
	LuaRef rot = readVariable<LuaRef>(parameterTable, "Rotation");
	rotation_ = Vector3D(rot[1], rot[2], rot[3]);
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

void Transform::preUpdate()
{
	node_->setScale(Vector3D::toOgre(scale));
	node_->setPosition(globalPosition_.toOgrePosition());
	node_->setOrientation(rotation_.toOgreRotation());
}

void Transform::lastUpdate()
{
	//ROTACION											TODO MATRICES DE TRANSFORMACIÓN PARA LOS EJES LOCALES
}

void Transform::physicsUpdate()
{
	setGlobalPosition(Vector3D::fromOgrePosition(node_->getPosition()));
	setRotation(Vector3D::fromOgreRotation(node_->getOrientation()));
}


void Transform::onEnable()
{
	node_->setScale(Vector3D::toOgre(scale));
	node_->setPosition(globalPosition_.toOgrePosition());
	node_->setOrientation(rotation_.toOgreRotation());
}

void Transform::setParent(Transform* parent)
{
	parent_ = parent;
	parent_->children_.push_back(this);
}

void Transform::eraseParent()
{
	parent_->removeChild(this);
	setParent(trRoot_.get());
}

void Transform::Translate(Vector3D t, bool global)
{
	if (global)
		moveGlobalPosition(t);
	else {
		;
	}
}

void Transform::Rotate(Vector3D r, bool global)
{
	node_->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(Ogre::Degree(r.x())), Ogre::Node::TS_WORLD);
	node_->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(Ogre::Degree(r.y())), Ogre::Node::TS_WORLD);
	node_->rotate(Ogre::Vector3(0, 0, 1), Ogre::Radian(Ogre::Degree(r.z())), Ogre::Node::TS_WORLD);
	rotation_ = Vector3D::fromOgreRotation(node_->getOrientation());
}

void Transform::Scale(Vector3D s)
{
	scale += s;
}

void Transform::setRotation(Vector3D v)
{
	rotation_ = v;
	node_->setOrientation(rotation_.toOgreRotation());
}

void Transform::setGlobalPosition(Vector3D v)
{
	globalPosition_ = v;
	position = globalPosition_ - parent_->globalPosition_;
}


void Transform::moveGlobalPosition(Vector3D v)
{
	globalPosition_ += v;
	position = globalPosition_ - parent_->globalPosition_;
}