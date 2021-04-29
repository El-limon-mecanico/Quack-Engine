#include "Transform.h"
#include "QuackEntity.h"
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

void Transform::cleanChildren()
{
	for (Transform* c : children_)
		c->parent_ = nullptr;
	children_.clear();
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
    hasParent() ? localPos_.set(Vector3D(x,y,z)-parent_->getLocalPos()) : localPos_.set(x,y,z);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D& pos) {
	hasParent() ? localPos_.set(pos - parent_->getLocalPos()):localPos_.set(pos);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D&& pos) {
	hasParent() ? localPos_.set(pos - parent_->getLocalPos()):localPos_.set(pos);
}
///set the value of vector which contains the pos
inline void Transform::setGlobalPos(Vector3D* pos) {
	hasParent() ? localPos_.set(Vector3D(pos) - parent_->getLocalPos()):localPos_.set(pos);
}
///set the value x of the pos vector
inline void Transform::setGlobalPosX(float x) {
	hasParent() ? localPos_.setX(x - parent_->getLocalPosX()) : localPos_.setX(x);
}
///set the value y of the pos vector
inline void Transform::setGlobalPosY(float y) {
	hasParent() ? localPos_.setY(y - parent_->getLocalPosY()):localPos_.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalPosZ(float z) {
	hasParent() ? localPos_.setZ(z - parent_->getLocalPosZ()):localPos_.setZ(z);
}
#pragma endregion

#pragma region globalScale

//set the value of vector which contains the pos
inline void Transform::setGlobalScale(float x, float y, float z) {
	hasParent() ? localScale_.set(Vector3D(x, y, z) - parent_->getLocalScale()):localScale_.set(x,y,z);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D& scale) {
	hasParent() ? localScale_.set(scale - parent_->getLocalScale()):localScale_.set(scale);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D&& scale) {
	hasParent() ? localScale_.set(scale - parent_->getLocalScale()):localScale_.set(scale);
}
///set the value of vector which contains the scale
inline void Transform::setGlobalScale(Vector3D* scale) {
	hasParent() ? localScale_.set(Vector3D(scale) - parent_->getLocalScale()):localScale_.set(scale);
}
///set the value x of the scale vector
inline void Transform::setGlobalScaleX(float x) {
	hasParent() ? localScale_.setX(x - parent_->getLocalScaleX()):localScale_.setX(x);
}
///set the value y of the scale vector
inline void Transform::setGlobalScaleY(float y) {
	hasParent() ? localScale_.setY(y - parent_->getLocalScaleY()):localScale_.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalScaleZ(float z) {
	hasParent() ? localScale_.setZ(z - parent_->getLocalScaleZ()):localScale_.setZ(z);
}
#pragma endregion

#pragma region globalRotation

//set the value of vector which contains the pos
inline void Transform::setGlobalRotation(float x, float y, float z) {
	hasParent() ? localRotation_.set(Vector3D(x, y, z) - parent_->getLocalRotation()):localRotation_.set(x,y,z);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D& rotation) {
	hasParent() ? localRotation_.set(rotation - parent_->getLocalRotation()):localRotation_.set(rotation);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D&& rotation) {
	hasParent() ? localRotation_.set(rotation - parent_->getLocalRotation()):localRotation_.set(rotation);
}
///set the value of vector which contains the rotation
inline void Transform::setGlobalRotation(Vector3D* rotation) {
	hasParent() ? localRotation_.set(Vector3D(rotation) - parent_->getLocalRotation()):localRotation_.set(rotation);
}
///set the value x of the rotation vector
inline void Transform::setGlobalRotationX(float x) {
	hasParent() ? localRotation_.setX(x - parent_->getLocalRotationX()):localRotation_.setX(x);
}
///set the value y of the rotation vector
inline void Transform::setGlobalRotationY(float y) {
	hasParent() ? localRotation_.setY(y - parent_->getLocalRotationY()):localRotation_.setY(y);
}
///set the value z of the rotation vector
inline void Transform::setGlobalRotationZ(float z) {
	hasParent() ? localRotation_.setZ(z - parent_->getLocalRotationZ()):localRotation_.setZ(z);
}
#pragma endregion
#pragma endregion