//Componente encargada de gestionar la posicion, la direccion y la escala de la entidad
#pragma once
#include "Component.h"

namespace Ogre {
	class SceneNode;
	//class Vector3;
}


class Transform :
	public Component
{
private:
	//Root
	Transform(Ogre::SceneNode* n);
	static std::unique_ptr<Transform> trRoot_;

	//Save the position of this transform

	Ogre::SceneNode* node_;
	std::vector<Transform*> children_;
	Transform* parent_;

	Vector3D localPos;
	Vector3D localRot;
	Vector3D localScale;

public:
	Transform(Vector3D pos = Vector3D(), Vector3D rot = Vector3D(), Vector3D scale = Vector3D(1, 1, 1));
	virtual ~Transform() {};
	
	static Transform* InitRoot();
	Transform* RootTransform();

	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	static std::string GetName() { return "Transform"; }

	inline Transform& operator=(const Transform& t) {
		position = t.position;
		scale = t.scale;
		rotation = t.rotation;
		entity_ = t.entity_;
		return *this;
	}
	inline Transform& operator=(Transform&& t) noexcept {
		position = t.position;
		scale = t.scale;
		rotation = t.rotation;
		t.entity_ = nullptr;
		return *this;
	}

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;
	void cleanChildren();
	inline int childrenCount() const { return children_.size(); }
	void addChild(Transform* child) { children_.push_back(child); child->setParent(this); }
	inline bool hasChild() const { return childrenCount() != 0; }
	inline bool hasParent() const { return parent_ != nullptr; }

	Ogre::SceneNode* getNode();
	virtual void physicsUpdate() override;
	virtual void lateUpdate() override;

	virtual void onDisable()override { enable = true; }

	inline std::vector<Transform*> getChildren() const { return children_; }
	inline QuackEntity* getChild(int n) const { return children_[n]->entity_; }
	inline QuackEntity* getParent() const { return parent_->entity_; }
	void setParent(Transform* parent) { parent_ = parent; }
	void eraseParent() { parent_ = trRoot_.get(); }

	inline QuackEntity* getChildByTag(std::string tag) const;
	inline QuackEntity* getChildByName(std::string name) const;


	void Translate(Vector3D t, bool global = false);
	void Rotate(Vector3D r, bool global = false);
	void Scale(Vector3D s, bool global = false);

#pragma endregion
};