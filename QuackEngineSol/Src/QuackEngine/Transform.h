//Componente encargada de gestionar la posicion, la direccion y la escala de la entidad
#pragma once
#include "Component.h"
#include "Vector3D.h"
class Transform :
	public Component
{
private:
	//Save the position of this transform
	Vector3D pos_;
	Vector3D scale_;
	Vector3D rotation_;
	std::vector<Transform*> children_;
	Transform* parent_;
public:
	Transform() {}
#pragma region Operators
	inline Transform& operator=(const Transform& t) {
		pos_ = t.pos_;
		scale_ = t.scale_;
		rotation_ = t.rotation_;
		entity_ = t.entity_;
		return *this;
	}
	inline Transform& operator=(Transform&& t) noexcept {
		pos_ = t.pos_;
		scale_ = t.scale_;
		rotation_ = t.rotation_;
		t.entity_ = nullptr;
		return *this;
	}
#pragma endregion
	virtual ~Transform() {};
	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	void cleanChildren();
	inline int childrenCount() const { return children_.size(); }
	void addChild(Transform* child) { children_.push_back(child); child->setParent(this); }
	inline bool hasChild() const { return childrenCount() != 0; }
	inline bool hasParent() const { return parent_ != nullptr; }

#pragma region getters
#pragma region pos_
	//Return the vector which contains the pos
	inline Vector3D getPos() const { return pos_; };
	inline Vector3D getGlobalPos() const;
	//Return the value of the x in pos vector
	inline float getPosX() const { return scale_.getX(); };
	inline float getGlobalPosX() const;
	//Return the value of the y in pos vector
	inline float getPosY() const { return scale_.getY(); };
	inline float getGlobalPosY() const;
	//Return the value of the z in pos vector
	inline float getPosZ() const { return scale_.getZ(); };
	inline float getGlobalPosZ() const;
#pragma endregion
#pragma region scale_
	//Return the vector which contains the scale
	inline Vector3D getScale() const { return scale_; };
	inline Vector3D getGlobalScale() const;
	//Return the value of the width
	inline float getScaleX() const { return scale_.getX(); };
	inline float getGlobalScaleX() const;
	//Return the value of the height
	inline float getScaleY() const { return scale_.getY(); };
	inline float getGlobalScaleY() const;
	//Return the value of the depth
	inline float getScaleZ() const { return scale_.getZ(); };
	inline float getGlobalScaleZ() const;
#pragma endregion
#pragma region rotation_
	//Return the vector which contains the scale
	inline Vector3D getRotation() const { return rotation_; };
	inline Vector3D getGlobalRotation() const;
	//Return the value of the the rotation in x
	inline float getRotationX() const { return rotation_.getX(); };
	inline float getGlobalRotationX() const;
	//Return the value of the the rotation in x
	inline float getRotationY() const { return rotation_.getY(); };
	inline float getGlobalRotationY() const;
	//Return the value of the the rotation in x
	inline float getRotationZ() const { return rotation_.getZ(); };
	inline float getGlobalRotationZ() const;
#pragma endregion
	inline std::vector<Transform*> getChildren() const { return children_; }
	inline QuackEntity* getChild(int n) const { return children_[n]->entity_; }
	inline QuackEntity* getParent() const { return parent_->entity_; }
	inline QuackEntity* getChildByTag(std::string tag) const;
	inline QuackEntity* getChildByName(std::string name) const;
	static std::string GetName() { return "Transform"; }
#pragma endregion

#pragma region setters
#pragma region pos_
	//set the value of vector which contains the pos
	inline void setPos(float x, float y, float z) { pos_.set(x, y, z); };
	///set the value of vector which contains the pos
	inline void setPos(Vector3D& pos) { pos_.set(pos); };
	///set the value of vector which contains the pos
	inline void setPos(Vector3D&& pos) { pos_.set(pos); };
	///set the value of vector which contains the pos
	inline void setPos(Vector3D* pos) { pos_.set(pos); };
	///set the value x of the pos vector
	inline void setPosX(float x) { pos_.setX(x); }
	///set the value y of the pos vector
	inline void setPosY(float y) { pos_.setY(y); }
	///set the value z of the rotation vector
	inline void setPosZ(float z) { rotation_.setZ(z); }

	//set the value of vector which contains the pos
	inline void setGlobalPos(float x, float y, float z);
	///set the value of vector which contains the pos
	inline void setGlobalPos(Vector3D& pos);
	///set the value of vector which contains the pos
	inline void setGlobalPos(Vector3D&& pos);
	///set the value of vector which contains the pos
	inline void setGlobalPos(Vector3D* pos);
	///set the value x of the pos vector
	inline void setGlobalPosX(float x);	///set the value y of the pos vector
	inline void setGlobalPosY(float y);
	///set the value z of the rotation vector
	inline void setGlobalPosZ(float z);
#pragma endregion
#pragma region scale_
	//set the value of vector which contains the scale
	inline void setScale(float x, float y, float z) { scale_.set(x, y, z); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D& scale) { scale_.set(scale); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D&& scale) { scale_.set(scale); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D* scale) { scale_.set(scale); };
	///set the value x of the scale vector
	inline void setScaleX(float x) { scale_.setX(x); }
	///set the value y of the scale vector
	inline void setScaleY(float y) { scale_.setY(y); }
	///set the value z of the rotation vector
	inline void setScaleZ(float z) { rotation_.setZ(z); }

	//set the value of vector which contains the scale
	inline void setGlobalScale(float x, float y, float z);
	///set the value of vector which contains the scale
	inline void setGlobalScale(Vector3D& scale);
	///set the value of vector which contains the scale
	inline void setGlobalScale(Vector3D&& scale);
	///set the value of vector which contains the scale
	inline void setGlobalScale(Vector3D* scale);
	///set the value x of the scale vector
	inline void setGlobalScaleX(float x);	///set the value y of the scale vector
	inline void setGlobalScaleY(float y);
	///set the value z of the rotation vector
	inline void setGlobalScaleZ(float z);
#pragma endregion
#pragma region rotation_
	//set the value of vector which contains the rotation
	inline void setRotation(float x, float y, float z) { rotation_.set(x, y, z); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D& rotation) { rotation_.set(rotation); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D&& rotation) { rotation_.set(rotation); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D* rotation) { rotation_.set(rotation); };
	///set the value x of the rotation vector
	inline void setRotationX(float x) { rotation_.setX(x); }
	///set the value y of the rotation vector
	inline void setRotationY(float y) { rotation_.setY(y); }
	///set the value z of the rotation vector
	inline void setRotationZ(float z) { rotation_.setZ(z); }

	//set the value of vector which contains the rotation
	inline void setGlobalRotation(float x, float y, float z);
	///set the value of vector which contains the rotation
	inline void setGlobalRotation(Vector3D& rotation);
	///set the value of vector which contains the rotation
	inline void setGlobalRotation(Vector3D&& rotation);
	///set the value of vector which contains the rotation
	inline void setGlobalRotation(Vector3D* rotation);
	///set the value x of the rotation vector
	inline void setGlobalRotationX(float x);	///set the value y of the rotation vector
	inline void setGlobalRotationY(float y);
	///set the value z of the rotation vector
	inline void setGlobalRotationZ(float z);
#pragma endregion
	void setParent(Transform* parent) { parent_ = parent; }
#pragma endregion
};