#include "Transform.h"
#include "QuackEntity.h"
bool Transform::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	setPos(pos[1], pos[2], pos[3]);
	LuaRef scale = readVariable<LuaRef>(parameterTable, "Scale");
	setScale(pos[1], pos[2], pos[3]);
	LuaRef rotation = readVariable<LuaRef>(parameterTable, "Rotation");
	setRotation(pos[1], pos[2], pos[3]);

	//TODO: HAY QUE METER LOS HIJOS POR LUA

	return true;
}

void Transform::cleanChildren()
{
	for (Transform* c : children_)
		c->parent_ = nullptr;
	children_.clear();
}

inline Vector3D Transform::getLocalPos() const
{
	if (!hasParent())
		return getPos();
	else
		return getPos() + parent_->getPos();
}

inline float Transform::getLocalPosX() const
{
	if (!hasParent())
		return getPosX();
	else
		return getPosX() + parent_->getPosX();
}

inline float Transform::getLocalPosY() const
{
	if (!hasParent())
		return getPosY();
	else
		return getPosY() + parent_->getPosY();
}

inline float Transform::getLocalPosZ() const
{
	if (!hasParent())
		return getPosZ();
	else
		return getPosZ() + parent_->getPosZ();
}

inline Vector3D Transform::getLocalScale() const
{
	if (!hasParent())
		return getScale();
	else
		return getScale() + parent_->getScale();
}

inline float Transform::getLocalScaleX() const
{
	if (!hasParent())
		return getScaleX();
	else
		return getScaleX() + parent_->getScaleX();
}

inline float Transform::getLocalScaleY() const
{
	if (!hasParent())
		return getScaleY();
	else
		return getScaleY() + parent_->getScaleY();
}

inline float Transform::getLocalScaleZ() const
{
	if (!hasParent())
		return getScaleZ();
	else
		return getScaleZ() + parent_->getScaleZ();
}

inline Vector3D Transform::getLocalRotation() const
{
	if (!hasParent())
		return getRotation();
	else
		return getRotation() + parent_->getRotation();
}

inline float Transform::getLocalRotationX() const
{
	if (!hasParent())
		return getRotationX();
	else
		return getRotationX() + parent_->getRotationX();
}

inline float Transform::getLocalRotationY() const
{
	if (!hasParent())
		return getRotationY();
	else
		return getRotationY() + parent_->getRotationY();
}

inline float Transform::getLocalRotationZ() const
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
