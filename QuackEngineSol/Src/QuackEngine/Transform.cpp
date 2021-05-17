#include "Transform.h"
#include "QuackEntity.h"
#include "Rigidbody.h"
#include <Ogre.h>
#include "OgreQuack.h"


Transform::Transform(Vector3D pos, Vector3D rot, Vector3D localScale_) : globalPosition_(pos), globalRotation_(rot), localScale_(localScale_)
{
	node_ = OgreQuack::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	setParent(trRoot_.get());
}

Transform::~Transform()
{
	parent_->getNode()->removeChild(node_);
	OgreQuack::Instance()->getSceneManager()->destroySceneNode(node_);
	node_ = nullptr;
}

Transform::Transform(Ogre::SceneNode* n) : globalPosition_(), globalRotation_(), localScale_(1, 1, 1),
right(1, 0, 0),
forward(0, 0, 1),
up(0, 1, 0)
{
	node_ = n;
	parent_ = this;
}
bool Transform::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	setGlobalPosition(Vector3D(pos[1], pos[2], pos[3]));
	LuaRef rot = readVariable<LuaRef>(parameterTable, "Rotation");
	setGlobalRotation(Vector3D(rot[1], rot[2], rot[3]));
	LuaRef scl = readVariable<LuaRef>(parameterTable, "Scale");
	setScale(Vector3D(scl[1], scl[2], scl[3]));

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

void Transform::physicsUpdateTr()
{
	localPosition_ = Vector3D::fromOgrePosition(node_->getPosition());
	globalPosition_ = Vector3D::fromOgrePosition(node_->_getDerivedPosition());
	globalRotation_ = Vector3D::fromOgreRotation(node_->_getDerivedOrientation());
	localRotation_ = Vector3D::fromOgreRotation(node_->getOrientation());
	recalculateAxes();
}


void Transform::onEnable()
{
	node_->setScale(Vector3D::toOgre(localScale_));
	node_->_setDerivedPosition(globalPosition_.toOgrePosition());
	node_->_setDerivedOrientation(globalRotation_.toOgreRotation());
}

void Transform::setParent(Transform* parent)
{
	if (parent_)
		parent_->node_->removeChild(node_);
	parent_ = parent;
	parent_->children_.push_back(this);
	if (parent_ != trRoot_.get() || !node_->getParent())
		parent_->node_->addChild(node_);
	recalculateAxes();
	setGlobalPosition(globalPosition_);
}

void Transform::eraseParent()
{
	parent_->removeChild(this);
	setParent(trRoot_.get());
	updateRb();
}

void Transform::Translate(Vector3D t, bool global)
{
	if (global)
		moveGlobalPosition(t);
	else {
		moveLocalPosition(t);
	}
}

void Transform::Rotate(Vector3D r, bool global)
{
	node_->rotate(Vector3D::toOgre(r), Ogre::Radian(Ogre::Degree(1)), global ? Ogre::Node::TS_WORLD : Ogre::Node::TS_LOCAL);
	globalRotation_ = Vector3D::fromOgreRotation(node_->_getDerivedOrientation());
	localRotation_ = Vector3D::fromOgreRotation(node_->getOrientation());
	recalculateAxes();
	updateRb();
	updateChildren();
}

void Transform::Scale(Vector3D s)
{
	node_->scale(Vector3D::toOgre(s));
	globalScale_ = node_->_getDerivedScale();
	localScale_ = node_->getScale();
	updateRb();
	updateChildren();
}

void Transform::setLocalRotation(Vector3D v)
{
	node_->setOrientation(v.toOgreRotation());
	globalRotation_ = Vector3D::fromOgreRotation(node_->_getDerivedOrientation());
	localRotation_ = Vector3D::fromOgreRotation(node_->getOrientation());
	recalculateAxes();
	updateRb();
	updateChildren();
}

void Transform::setGlobalRotation(Vector3D v)
{
	node_->_setDerivedOrientation(v.toOgreRotation());
	globalRotation_ = Vector3D::fromOgreRotation(node_->_getDerivedOrientation());
	localRotation_ = Vector3D::fromOgreRotation(node_->getOrientation());
	recalculateAxes();
	updateRb();
	updateChildren();
}

void Transform::setGlobalPosition(Vector3D v)
{
	node_->_setDerivedPosition(v.toOgrePosition());
	localPosition_ = Vector3D::fromOgrePosition(node_->getPosition());
	globalPosition_ = Vector3D::fromOgrePosition(node_->_getDerivedPosition());
	updateRb();
	updateChildren();
}


void Transform::setLocalPosition(Vector3D v)
{
	node_->setPosition(v.toOgrePosition());
	localPosition_ = Vector3D::fromOgrePosition(node_->getPosition());
	globalPosition_ = Vector3D::fromOgrePosition(node_->_getDerivedPosition());
	updateRb();
	updateChildren();
}

void Transform::setScale(Vector3D v)
{
	node_->setScale(Vector3D::toOgre(v));
	globalScale_ = node_->_getDerivedScale();
	localScale_ = node_->getScale();
	updateRb();
	updateChildren();

}

void Transform::moveGlobalPosition(Vector3D v)
{
	node_->translate(v.toOgrePosition(), Ogre::Node::TS_WORLD);
	globalPosition_ = Vector3D::fromOgrePosition(node_->_getDerivedPosition());
	localPosition_ = Vector3D::fromOgrePosition(node_->getPosition());
	updateRb();
	updateChildren();
}

void Transform::moveLocalPosition(Vector3D v)
{
	node_->translate(v.toOgrePosition(), Ogre::Node::TS_LOCAL);
	localPosition_ = Vector3D::fromOgrePosition(node_->getPosition());
	globalPosition_ = Vector3D::fromOgrePosition(node_->_getDerivedPosition());
	updateRb();
	updateChildren();
}

void Transform::recalculateAxes()
{
	right = node_->_getDerivedOrientation().xAxis();
	up = node_->_getDerivedOrientation().yAxis();
	forward = node_->_getDerivedOrientation().zAxis();
}


void Transform::updateChildren()
{
	for (Transform* t : children_)
		t->recalculateTransform();
}

void Transform::recalculateTransform()
{
	if (entity_ && entity_->name() == "Mono") {
		std::cout << globalPosition_ << "\n";
		std::cout << node_->_getDerivedPosition() << "\n";
	}
	//globalPosition_ = Vector3D::localToGlobalPosition(localPosition_, parent_->globalPosition_, parent_->globalRotation_);
	localPosition_ = Vector3D::fromOgrePosition(node_->getPosition());
	globalPosition_ = Vector3D::fromOgrePosition(node_->_getDerivedPosition());
	localScale_ = node_->getScale();
	globalScale_ = node_->_getDerivedScale();
	recalculateAxes();
	updateRb();
	updateChildren();
}

void Transform::updateRb()
{
	if (entity_) {
		Rigidbody* rb = entity_->getComponent<Rigidbody>();
		if (rb) {
			rb->resetTransform();
		}
	}
}
