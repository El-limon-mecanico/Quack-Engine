//Componente encargada de gestionar la posicion, la direccion y la escala de la entidad
#pragma once
#include "Component.h"
#include "Vector3D.h"


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
	static Transform* trRoot_;

	//Save the position of this transform

	Ogre::SceneNode* node_;
	std::vector<Transform*> children_;
	Transform* parent_;
public:
	Transform(Vector3D pos = Vector3D(), Vector3D rot = Vector3D(), Vector3D scale = Vector3D(1, 1, 1));
	virtual ~Transform() {};

	Vector3D position;
	Vector3D rotate;
	Vector3D scale;

	inline Transform& operator=(const Transform& t) {
		position = t.position;
		scale = t.scale;
		rotate = t.rotate;
		entity_ = t.entity_;
		return *this;
	}
	inline Transform& operator=(Transform&& t) noexcept {
		position = t.position;
		scale = t.scale;
		rotate = t.rotate;
		t.entity_ = nullptr;
		return *this;
	}

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;
	static bool InitRoot();
	void cleanChildren();
	inline int childrenCount() const { return children_.size(); }
	void addChild(Transform* child) { children_.push_back(child); child->setParent(this); }
	inline bool hasChild() const { return childrenCount() != 0; }
	inline bool hasParent() const { return parent_ != nullptr; }

	Ogre::SceneNode* getNode();
	virtual void preUpdate() override;
	virtual void update() override;
	virtual void lateUpdate() override;


//-GETTERS LOCALES: Sirven para obtener la posición de un objeto RELATIVA A SU PADRE. La posición guardada en el transform SIEMPRE será la relativa.
	//Estos métodos devuelven la posición local con respecto al padre que guarda un objeto.
//-GETTERS GLOBALES: Sirven para obtener la posición de un objeto EN EL MUNDO. Estos métodos devuelven la suma de la posición local + la posición local del padre.
#pragma region getters
#pragma region pos_
	//Return the vector which contains the pos
	inline Vector3D getLocalPos() const { return position; };
	inline Vector3D getGlobalPos() const;
	//Return the value of the x in pos vector
	inline float getLocalPosX() const { return scale.getX(); };
	inline float getGlobalPosX() const;
	//Return the value of the y in pos vector
	inline float getLocalPosY() const { return scale.getY(); };
	inline float getGlobalPosY() const;
	//Return the value of the z in pos vector
	inline float getLocalPosZ() const { return scale.getZ(); };
	inline float getGlobalPosZ() const;
#pragma endregion
#pragma region scale_
	//Return the vector which contains the scale
	inline Vector3D getLocalScale() const { return scale; };
	inline Vector3D getGlobalScale() const;
	//Return the value of the width
	inline float getLocalScaleX() const { return scale.getX(); };
	inline float getGlobalScaleX() const;
	//Return the value of the height
	inline float getLocalScaleY() const { return scale.getY(); };
	inline float getGlobalScaleY() const;
	//Return the value of the depth
	inline float getLocalScaleZ() const { return scale.getZ(); };
	inline float getGlobalScaleZ() const;
#pragma endregion
#pragma region rotation_
	//Return the vector which contains the scale
	inline Vector3D getLocalRotation() const { return rotate; };
	inline Vector3D getGlobalRotation() const;
	//Return the value of the the rotation in x
	inline float getLocalRotationX() const { return rotate.getX(); };
	inline float getGlobalRotationX() const;
	//Return the value of the the rotation in x
	inline float getLocalRotationY() const { return rotate.getY(); };
	inline float getGlobalRotationY() const;
	//Return the value of the the rotation in x
	inline float getLocalRotationZ() const { return rotate.getZ(); };
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
	inline void setLocalPos(float x, float y, float z) { position.set(x, y, z); };
	///set the vsetLocalPosf vector which contains the pos
	inline void setLocalPos(Vector3D& pos) { position.set(pos); };
	///set the vsetLocalPosf vector which contains the pos
	inline void setLocalPos(Vector3D&& pos) { position.set(pos); };
	///set the vsetLocalPosf vector which contains the pos
	inline void setLocalPos(Vector3D* pos) { position.set(pos); };
	///set the vsetLocalPos of the pos vector
	inline void setLocalPosX(float x) { position.setX(x); }
	///set the vsetLocalPos of the pos vector
	inline void setLocalPosY(float y) { position.setY(y); }
	///set the vsetLocalPos of the rotation vector
	inline void setLocalPosZ(float z) { rotate.setZ(z); }

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
	inline void setScale(float x, float y, float z) { scale.set(x, y, z); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D& scale) { scale.set(scale); };
	///set the value of vector which contains the scale
	inline void setScale(Vector3D&& scale) { scale.set(scale); };
	///set the value of vector which contains the scale
	//inline void setScale(Vector3D* scale) { scale.set(scale); };
	///set the value x of the scale vector
	inline void setScaleX(float x) { scale.setX(x); }
	///set the value y of the scale vector
	inline void setScaleY(float y) { scale.setY(y); }
	///set the value z of the rotation vector
	inline void setScaleZ(float z) { rotate.setZ(z); }

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
	inline void setRotation(float x, float y, float z) { rotate.set(x, y, z); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D& rotation) { rotate.set(rotation); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D&& rotation) { rotate.set(rotation); };
	///set the value of vector which contains the rotation
	inline void setRotation(Vector3D* rotation) { rotate.set(rotation); };
	///set the value x of the rotation vector
	inline void setRotationX(float x) { rotate.setX(x); }
	///set the value y of the rotation vector
	inline void setRotationY(float y) { rotate.setY(y); }
	///set the value z of the rotation vector
	inline void setRotationZ(float z) { rotate.setZ(z); }

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

	//Vector3D vectorToOgre(Ogre::Vector3 v);

#pragma endregion
};