#include "Transform.h"
#include "QuackEntity.h"
#include "Rigidbody.h"
#include <Ogre.h>
#include "OgreQuack.h"


Transform::Transform(Vector3D pos, Vector3D rot, Vector3D localScale_) : globalPosition_(pos), globalRotation_(rot), localScale_(localScale_)
{
	transform = this;
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
	transform = this;
	node_ = n;
	parent_ = this;
}

bool Transform::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = NULL, rot = NULL, scl = NULL;
	bool correct = true;
	correct &= readVariable<LuaRef>(parameterTable, "Position", &pos);
	correct &= readVariable<LuaRef>(parameterTable, "Rotation", &rot);
	correct &= readVariable<LuaRef>(parameterTable, "Scale", &scl);

	if (!correct) return false;

	setGlobalPosition(Vector3D(pos[1], pos[2], pos[3]));
	setGlobalRotation(Vector3D(rot[1], rot[2], rot[3]));
	setScale(Vector3D(scl[1], scl[2], scl[3]));

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
		i++;
	}
	return nullptr;
}
inline QuackEntity* Transform::getChildByName(std::string name) const
{
	int i = 0;
	while (i < childrenCount()) {
		if (name == children_[i]->entity_->name())
			return children_[i]->entity_;
		i++;
	}
	return nullptr;
}

Ogre::SceneNode* Transform::getNode()
{
	return node_;
}

void Transform::physicsUpdateTr()
{
	recalculatePosition();
	recalculateAxes();
	updateChildren();
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
	node_->rotate({ 1,0,0 }, Ogre::Radian(Ogre::Degree(r.x)), global ? Ogre::Node::TS_WORLD : Ogre::Node::TS_LOCAL);
	node_->rotate({ 0,1,0 }, Ogre::Radian(Ogre::Degree(r.y)), global ? Ogre::Node::TS_WORLD : Ogre::Node::TS_LOCAL);
	node_->rotate({ 0,0,1 }, Ogre::Radian(Ogre::Degree(r.z)), global ? Ogre::Node::TS_WORLD : Ogre::Node::TS_LOCAL);
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
	node_->resetOrientation();
	Rotate(v);
}

void Transform::setGlobalRotation(Vector3D v)
{
	node_->resetOrientation();
	Rotate(v, true);
}

void Transform::setGlobalPosition(Vector3D v)
{
	node_->_setDerivedPosition(v.toOgrePosition());
	recalculatePosition();
	updateRb();
	updateChildren();
}

void Transform::setLocalPosition(Vector3D v)
{
	node_->setPosition(v.toOgrePosition());
	recalculatePosition();
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
	recalculatePosition();
	updateRb();
	updateChildren();
}

void Transform::moveLocalPosition(Vector3D v)
{
	node_->translate(v.toOgrePosition(), Ogre::Node::TS_LOCAL);
	recalculatePosition();
	updateRb();
	updateChildren();
}

void Transform::recalculateAxes()
{
	globalRotation_ = Vector3D::fromOgreRotation(node_->_getDerivedOrientation());
	localRotation_ = Vector3D::fromOgreRotation(node_->getOrientation());
	right = node_->_getDerivedOrientation().xAxis();
	up = node_->_getDerivedOrientation().yAxis();
	forward = node_->_getDerivedOrientation().zAxis();
}

void Transform::recalculatePosition()
{
	globalPosition_ = Vector3D::fromOgrePosition(node_->_getDerivedPosition());
	localPosition_ = Vector3D::fromOgrePosition(node_->getPosition());
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

void Transform::lookAt(Transform* tr, TrAxis axis)
{
	lookAt(tr->globalPosition_, axis);
}

void Transform::lookAt(Vector3D point, TrAxis axis)
{
	Ogre::Vector3 v;

	switch (axis)
	{
	case X_AXIS:
		v = Ogre::VectorBase<3, Ogre::Real>::UNIT_X;
		break;
	case Y_AXIS:
		v = Ogre::VectorBase<3, Ogre::Real>::UNIT_Y;
		break;
	case Z_AXIS:
		v = Ogre::VectorBase<3, Ogre::Real>::UNIT_Z;
		break;
	case NEGATIVE_X_AXIS:
		v = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_X;
		break;
	case NEGATIVE_Y_AXIS:
		v = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Y;
		break;
	case NEGATIVE_Z_AXIS:
		v = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z;
		break;
	default:
		v = Ogre::VectorBase<3, Ogre::Real>::UNIT_Z;
		break;
	}

	node_->lookAt(point.toOgrePosition(), Ogre::Node::TS_WORLD, v);
	recalculateAxes();
	updateRb();
	updateChildren();
}