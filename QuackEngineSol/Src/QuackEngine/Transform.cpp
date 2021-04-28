#include "Transform.h"
#include "QuackEntity.h"
bool Transform::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	setPos(pos[1], pos[2], pos[3]);
	LuaRef scale = readVariable<LuaRef>(parameterTable, "Scale");
	setScale(scale[1], scale[2], scale[3]);
	LuaRef rotation = readVariable<LuaRef>(parameterTable, "Rotation");
	setRotation(rotation[1], rotation[2], rotation[3]);

	//TODO: HAY QUE METER LOS HIJOS POR LUA

	return true;
}

void Transform::cleanChildren()
{
	for (Transform* c : children_)
		c->parent_ = nullptr;
	children_.clear();
}

inline Vector3D Transform::getGlobalPos() const
{
	if (!hasParent())
		return getPos();
	else
		return getPos() + parent_->getPos();
}

inline float Transform::getGlobalPosX() const
{
	if (!hasParent())
		return getPosX();
	else
		return getPosX() + parent_->getPosX();
}

inline float Transform::getGlobalPosY() const
{
	if (!hasParent())
		return getPosY();
	else
		return getPosY() + parent_->getPosY();
}

inline float Transform::getGlobalPosZ() const
{
	if (!hasParent())
		return getPosZ();
	else
		return getPosZ() + parent_->getPosZ();
}

inline Vector3D Transform::getGlobalScale() const
{
	if (!hasParent())
		return getScale();
	else
		return getScale() + parent_->getScale();
}

inline float Transform::getGlobalScaleX() const
{
	if (!hasParent())
		return getScaleX();
	else
		return getScaleX() + parent_->getScaleX();
}

inline float Transform::getGlobalScaleY() const
{
	if (!hasParent())
		return getScaleY();
	else
		return getScaleY() + parent_->getScaleY();
}

inline float Transform::getGlobalScaleZ() const
{
	if (!hasParent())
		return getScaleZ();
	else
		return getScaleZ() + parent_->getScaleZ();
}

inline Vector3D Transform::getGlobalRotation() const
{
	if (!hasParent())
		return getRotation();
	else
		return getRotation() + parent_->getRotation();
}

inline float Transform::getGlobalRotationX() const
{
	if (!hasParent())
		return getRotationX();
	else
		return getRotationX() + parent_->getRotationX();
}

inline float Transform::getGlobalRotationY() const
{
	if (!hasParent())
		return getRotationY();
	else
		return getRotationY() + parent_->getRotationY();
}

inline float Transform::getGlobalRotationZ() const
{
	if (!hasParent())
		return getRotationZ();
	else
		return getRotationZ() + parent_->getRotationZ();
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
    parent_!=nullptr ? pos_.set(Vector3D(x,y,z)-parent_->getPos()) : pos_.set(x,y,z);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D& pos) {
	parent_ != nullptr ? pos_.set(pos - parent_->getPos()):pos_.set(pos);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D&& pos) {
	parent_ != nullptr ? pos_.set(pos - parent_->getPos()):pos_.set(pos);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D* pos) {
	parent_ != nullptr ? pos_.set(Vector3D(pos) - parent_->getPos()):pos_.set(pos);
}
///set the value x of the pos vector
inline void Transform::setGlobalPosX(float x) {
	parent_ != nullptr ? pos_.setX(x - parent_->getPosX()) : pos_.setX(x);
}
///set the value y of the pos vector
inline void Transform::setGlobalPosY(float y) {
	parent_ != nullptr ? pos_.setY(y - parent_->getPosY()):pos_.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalPosZ(float z) {
	parent_ != nullptr ? pos_.setZ(z - parent_->getPosZ()):pos_.setZ(z);
}
#pragma endregion

#pragma region globalScale

//set the value of vector which contains the pos
inline void Transform::setGlobalScale(float x, float y, float z) {
	parent_ != nullptr ? scale_.set(Vector3D(x, y, z) - parent_->getScale()):scale_.set(x,y,z);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D& scale) {
	parent_ != nullptr ? scale_.set(scale - parent_->getScale()):scale_.set(scale);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D&& scale) {
	parent_ != nullptr ? scale_.set(scale - parent_->getScale()):scale_.set(scale);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D* scale) {
	parent_ != nullptr ? scale_.set(Vector3D(scale) - parent_->getScale()):scale_.set(scale);
}
///set the value x of the scale vector
inline void Transform::setGlobalScaleX(float x) {
	parent_ != nullptr ? scale_.setX(x - parent_->getScaleX()):scale_.setX(x);
}
///set the value y of the scale vector
inline void Transform::setGlobalScaleY(float y) {
	parent_ != nullptr ? scale_.setY(y - parent_->getScaleY()):scale_.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalScaleZ(float z) {
	parent_ != nullptr ? scale_.setZ(z - parent_->getScaleZ()):scale_.setZ(z);
}
#pragma endregion

#pragma region globalRotation

//set the value of vector which contains the pos
inline void Transform::setGlobalRotation(float x, float y, float z) {
	parent_ != nullptr ? rotation_.set(Vector3D(x, y, z) - parent_->getRotation()):rotation_.set(x,y,z);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D& rotation) {
	parent_ != nullptr ? rotation_.set(rotation - parent_->getRotation()):rotation_.set(rotation);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D&& rotation) {
	parent_ != nullptr ? rotation_.set(rotation - parent_->getRotation()):rotation_.set(rotation);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D* rotation) {
	parent_ != nullptr ? rotation_.set(Vector3D(rotation) - parent_->getRotation()):rotation_.set(rotation);
}
///set the value x of the rotation vector
inline void Transform::setGlobalRotationX(float x) {
	parent_ != nullptr ? rotation_.setX(x - parent_->getRotationX()):rotation_.setX(x);
}
///set the value y of the rotation vector
inline void Transform::setGlobalRotationY(float y) {
	parent_ != nullptr ? rotation_.setY(y - parent_->getRotationY()):rotation_.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalRotationZ(float z) {
	parent_ != nullptr ? rotation_.setZ(z - parent_->getRotationZ()):rotation_.setZ(z);
}
#pragma endregion
#pragma endregion