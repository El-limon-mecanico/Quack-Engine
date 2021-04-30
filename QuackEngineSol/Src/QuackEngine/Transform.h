//Componente encargada de gestionar la posicion, la direccion y la escala de la entidad
#pragma once
#include "Component.h"
#include "Vector3D.h"
class Transform :
	public Component
{
private:
	//Save the position of this transform
	Vector3D localPos_;
	Vector3D localScale_;
	Vector3D localRotation_;
	std::vector<Transform*> children_;
	Transform* parent_;
public:
	Transform() {}
#pragma region Operators
	inline Transform& operator=(const Transform& t) {
		localPos_ = t.localPos_;
		localScale_ = t.localScale_;
		localRotation_ = t.localRotation_;
		entity_ = t.entity_;
		return *this;
	}
	inline Transform& operator=(Transform&& t) noexcept {
		localPos_ = t.localPos_;
		localScale_ = t.localScale_;
		localRotation_ = t.localRotation_;
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

//-GETTERS LOCALES: Sirven para obtener la posición de un objeto RELATIVA A SU PADRE. La posición guardada en el transform SIEMPRE será la relativa.
	//Estos métodos devuelven la posición local con respecto al padre que guarda un objeto.
//-GETTERS GLOBALES: Sirven para obtener la posición de un objeto EN EL MUNDO. Estos métodos devuelven la suma de la posición local + la posición local del padre.
#pragma region getters
#pragma region pos_
	//Return the vector which contains the pos
	inline Vector3D getLocalPos() const { return localPos_; };
	inline Vector3D getGlobalPos() const;
	//Return the value of the x in pos vector
	inline float getLocalPosX() const { return localScale_.getX(); };
	inline float getGlobalPosX() const;
	//Return the value of the y in pos vector
	inline float getLocalPosY() const { return localScale_.getY(); };
	inline float getGlobalPosY() const;
	//Return the value of the z in pos vector
	inline float getLocalPosZ() const { return localScale_.getZ(); };
	inline float getGlobalPosZ() const;
#pragma endregion
#pragma region scale_
	//Return the vector which contains the scale
	inline Vector3D getLocalScale() const { return localScale_; };
	inline Vector3D getGlobalScale() const;
	//Return the value of the width
	inline float getLocalScaleX() const { return localScale_.getX(); };
	inline float getGlobalScaleX() const;
	//Return the value of the height
	inline float getLocalScaleY() const { return localScale_.getY(); };
	inline float getGlobalScaleY() const;
	//Return the value of the depth
	inline float getLocalScaleZ() const { return localScale_.getZ(); };
	inline float getGlobalScaleZ() const;
#pragma endregion
#pragma region rotation_
	//Return the vector which contains the scale
	inline Vector3D getLocalRotation() const { return localRotation_; };
	inline Vector3D getGlobalRotation() const;
	//Return the value of the the rotation in x
	inline float getLocalRotationX() const { return localRotation_.getX(); };
	inline float getGlobalRotationX() const;
	//Return the value of the the rotation in x
	inline float getLocalRotationY() const { return localRotation_.getY(); };
	inline float getGlobalRotationY() const;
	//Return the value of the the rotation in x
	inline float getLocalRotationZ() const { return localRotation_.getZ(); };
	inline float getGlobalRotationZ() const;
#pragma endregion
	inline std::vector<Transform*> getChildren() const { return children_; }
	inline QuackEntity* getChild(int n) const { return children_[n]->entity_; }
	inline QuackEntity* getParent() const { return parent_->entity_; }
	inline QuackEntity* getChildByTag(std::string tag) const;
	inline QuackEntity* getChildByName(std::string name) const;
	static std::string GetName() { return "Transform"; }
#pragma endregion
//-SETTERS LOCALES: Sirven para cambiar la posición de un objeto RELATIVA A SU PADRE. La posición guardada en el transform SIEMPRE será la relativa.
	//Modifican la posición relativa al padre de manera directa, indicando a cuantas unidades debe estar alejado del padre.
//-SETTERS GLOBALES: Sirven para cambiar la posición de un objeto RELATIVA AL MUNDO. Estos métodos modifican la posicion relativa al padre a través de una
	//posición en coordenadas mundiales.
#pragma region setters
	
#pragma region pos_
	

	//set the value of vector which contains the pos
	inline void setLocalPos(float x, float y, float z) { localPos_.set(x, y, z); };
	///set the vsetLocalPosf vector which contains the pos
	inline void setLocalPos(Vector3D& pos) { localPos_.set(pos); };
	///set the vsetLocalPosf vector which contains the pos
	inline void setLocalPos(Vector3D&& pos) { localPos_.set(pos); };
	///set the vsetLocalPosf vector which contains the pos
	inline void setLocalPos(Vector3D* pos) { localPos_.set(pos); };
	///set the vsetLocalPos of the pos vector
	inline void setLocalPosX(float x) { localPos_.setX(x); }
	///set the vsetLocalPos of the pos vector
	inline void setLocalPosY(float y) { localPos_.setY(y); }
	///set the vsetLocalPos of the rotation vector
	inline void setLocalPosZ(float z) { localRotation_.setZ(z); }

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
	inline void setScale(float x, float y, float z) { localScale_.set(x, y, z); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D& scale) { localScale_.set(scale); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D&& scale) { localScale_.set(scale); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D* scale) { localScale_.set(scale); };
	///set the value x of the scale vector
	inline void setScaleX(float x) { localScale_.setX(x); }
	///set the value y of the scale vector
	inline void setScaleY(float y) { localScale_.setY(y); }
	///set the value z of the rotation vector
	inline void setScaleZ(float z) { localRotation_.setZ(z); }

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
	inline void setRotation(float x, float y, float z) { localRotation_.set(x, y, z); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D& rotation) { localRotation_.set(rotation); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D&& rotation) { localRotation_.set(rotation); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D* rotation) { localRotation_.set(rotation); };
	///set the value x of the rotation vector
	inline void setRotationX(float x) { localRotation_.setX(x); }
	///set the value y of the rotation vector
	inline void setRotationY(float y) { localRotation_.setY(y); }
	///set the value z of the rotation vector
	inline void setRotationZ(float z) { localRotation_.setZ(z); }

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
	void eraseParent() { parent_ = nullptr; }
#pragma endregion
};