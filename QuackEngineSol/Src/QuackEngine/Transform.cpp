#include "Transform.h"
#include "QuackEntity.h"
#include <Ogre.h>
#include "OgreQuack.h"
Transform::Transform(Vector3D pos, Vector3D rot, Vector3D scale): position(pos), rotate(rot), scale(scale)
{
	node_ = OgreQuack::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	setParent(trRoot_);
}
Transform::Transform(Ogre::SceneNode* n) : position(), rotate(), scale(1,1,1) {
	node_ = n;
	setParent(this);
}
bool Transform::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	setLocalPos(pos[1], pos[2], pos[3]);
	LuaRef scale = readVariable<LuaRef>(parameterTable, "Scale");
	setScale(scale[1], scale[2], scale[3]);
	LuaRef rotation = readVariable<LuaRef>(parameterTable, "Rotation");
	setRotation(rotation[1], rotation[2], rotation[3]);

	//TODO: HAY QUE METER LOS HIJOS POR LUA

	return true;
}

bool Transform::InitRoot()
{
	trRoot_ = new Transform(OgreQuack::Instance()->getSceneManager()->getRootSceneNode());
	return trRoot_;
}

void Transform::cleanChildren()
{
	for (Transform* c : children_)
		c->parent_ = nullptr;
	children_.clear();
}


Ogre::SceneNode* Transform::getNode()
{
	return node_;
}

void Transform::preUpdate()
{

}

void Transform::update()
{

}

void Transform::lateUpdate()
{
	//Ogre::Vector3 p = node_->getPosition().x;
	position = Vector3D();
}

inline Vector3D Transform::getGlobalPos() const
{
	if (!hasParent())
		return getLocalPos(); 
	else
		return getLocalPos() + parent_->getLocalPos();
}

inline float Transform::getGlobalPosX() const
{
	if (!hasParent())
		return getLocalPosX();
	else
		return getLocalPosX() + parent_->getLocalPosX();
}

inline float Transform::getGlobalPosY() const
{
	if (!hasParent())
		return getLocalPosY();
	else
		return getLocalPosY() + parent_->getLocalPosY();
}

inline float Transform::getGlobalPosZ() const
{
	if (!hasParent())
		return getLocalPosZ();
	else
		return getLocalPosZ() + parent_->getLocalPosZ();
}

inline Vector3D Transform::getGlobalScale() const
{
	if (!hasParent())
		return getLocalScale();
	else
		return getLocalScale() + parent_->getLocalScale();
}

inline float Transform::getGlobalScaleX() const
{
	if (!hasParent())
		return getLocalScaleX();
	else
		return getLocalScaleX() + parent_->getLocalScaleX();
}

inline float Transform::getGlobalScaleY() const
{
	if (!hasParent())
		return getLocalScaleY();
	else
		return getLocalScaleY() + parent_->getLocalScaleY();
}

inline float Transform::getGlobalScaleZ() const
{
	if (!hasParent())
		return getLocalScaleZ();
	else
		return getLocalScaleZ() + parent_->getLocalScaleZ();
}

inline Vector3D Transform::getGlobalRotation() const
{
	if (!hasParent())
		return getLocalRotation();
	else
		return getLocalRotation() + parent_->getLocalRotation();
}

inline float Transform::getGlobalRotationX() const
{
	if (!hasParent())
		return getLocalRotationX();
	else
		return getLocalRotationX() + parent_->getLocalRotationX();
}

inline float Transform::getGlobalRotationY() const
{
	if (!hasParent())
		return getLocalRotationY();
	else
		return getLocalRotationY() + parent_->getLocalRotationY();
}

inline float Transform::getGlobalRotationZ() const
{
	if (!hasParent())
		return getLocalRotationZ();
	else
		return getLocalRotationZ() + parent_->getLocalRotationZ();
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
#pragma region globalSetters

#pragma region globalPos

//set the value of vector which contains the pos
inline void Transform::setGlobalPos(float x, float y, float z) {
    hasParent() ? position.set(Vector3D(x,y,z)-parent_->getLocalPos()) : position.set(x,y,z);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D& pos) {
	hasParent() ? position.set(pos - parent_->getLocalPos()):position.set(pos);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D&& pos) {
	hasParent() ? position.set(pos - parent_->getLocalPos()):position.set(pos);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D* pos) {
	hasParent() ? position.set(Vector3D(pos) - parent_->getLocalPos()):position.set(pos);
}
///set the value x of the pos vector
inline void Transform::setGlobalPosX(float x) {
	hasParent() ? position.setX(x - parent_->getLocalPosX()) : position.setX(x);
}
///set the value y of the pos vector
inline void Transform::setGlobalPosY(float y) {
	hasParent() ? position.setY(y - parent_->getLocalPosY()):position.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalPosZ(float z) {
	hasParent() ? position.setZ(z - parent_->getLocalPosZ()):position.setZ(z);
}
#pragma endregion

#pragma region globalScale

//set the value of vector which contains the pos
inline void Transform::setGlobalScale(float x, float y, float z) {
	hasParent() ? scale.set(Vector3D(x, y, z) - parent_->getLocalScale()):scale.set(x,y,z);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D& setscale) {
	hasParent() ? scale.set(scale - parent_->getLocalScale()):scale.set(scale);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D&& setscale) {
	hasParent() ? scale.set(scale - parent_->getLocalScale()):scale.set(scale);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D* scale) {
	hasParent() ? scale.set(Vector3D(scale) - parent_->getLocalScale()):scale.set(scale);
}
///set the value x of the scale vector
inline void Transform::setGlobalScaleX(float x) {
	hasParent() ? scale.setX(x - parent_->getLocalScaleX()):scale.setX(x);
}
///set the value y of the scale vector
inline void Transform::setGlobalScaleY(float y) {
	hasParent() ? scale.setY(y - parent_->getLocalScaleY()):scale.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalScaleZ(float z) {
	hasParent() ? scale.setZ(z - parent_->getLocalScaleZ()):scale.setZ(z);
}
#pragma endregion

#pragma region globalRotation

//set the value of vector which contains the pos
inline void Transform::setGlobalRotation(float x, float y, float z) {
	hasParent() ? rotate.set(Vector3D(x, y, z) - parent_->getLocalRotation()):rotate.set(x,y,z);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D& rotation) {
	hasParent() ? rotate.set(rotation - parent_->getLocalRotation()):rotate.set(rotation);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D&& rotation) {
	hasParent() ? rotate.set(rotation - parent_->getLocalRotation()):rotate.set(rotation);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D* rotation) {
	hasParent() ? rotate.set(Vector3D(rotation) - parent_->getLocalRotation()):rotate.set(rotation);
}
///set the value x of the rotation vector
inline void Transform::setGlobalRotationX(float x) {
	hasParent() ? rotate.setX(x - parent_->getLocalRotationX()):rotate.setX(x);
}
///set the value y of the rotation vector
inline void Transform::setGlobalRotationY(float y) {
	hasParent() ? rotate.setY(y - parent_->getLocalRotationY()):rotate.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalRotationZ(float z) {
	hasParent() ? rotate.setZ(z - parent_->getLocalRotationZ()):rotate.setZ(z);
}

#pragma endregion
#pragma endregion