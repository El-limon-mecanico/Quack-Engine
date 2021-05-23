// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <cmath>
#include <ostream>

/*
 * A class implementing a 3-dimensional vector and corresponding
 * operations. All operations generate new Vector3D, they do not
 * modify the vectors on which they operate. The only methods that
 * modify the state are the different setters (and operator=).
 *
 */

namespace Ogre {
	template<int dims, typename T>
	class Vector;
	typedef float Real;
	typedef Vector<3, Real> Vector3;
	class Quaternion;
	class Matrix4;
	class Matrix3;
}

class btVector3;
class btQuaternion;

class QUACK_ENGINE_PRO_API Vector3D {
public:
	float x;  // First coordinate
	float y;  // Second coordinate
	float z;  // Third coordinate

	// various constructors
	Vector3D() noexcept :
		x(), y(), z() {
	}

	Vector3D(float value) :
		x(value), y(value), z(value) {
	}
	

	Vector3D(const Vector3D& v) :
		x(v.x), y(v.y), z(v.z) {
	}

	Vector3D(Vector3D&& v) :
		x(v.x), y(v.y), z(v.z) {
	}

	Vector3D(const Vector3D* v) :
		x(v->x), y(v->y), z(v->z) {
	}

	Vector3D(float x, float y, float z) :
		x(x), y(y), z(z) {
	}

	Vector3D(Ogre::Vector3 v);

	Vector3D(btVector3 v);

	~Vector3D() {
	}


	Ogre::Vector3 toOgrePosition();

	btVector3 toBulletPosition();

	Ogre::Quaternion toOgreRotation();

	btQuaternion toBulletRotation();

	btVector3 toBullet();

	Ogre::Vector3 toOgre();

	static Vector3D up() { return { 0,1,0 }; }

	static Vector3D rigth() { return { 1,0,0 }; }

	static Vector3D forward() { return { 0,0,1 }; }

	static Ogre::Vector3 toOgre(Vector3D v);

	static btVector3 toBullet(Vector3D v);

	static Vector3D fromOgre(Ogre::Vector3 v);

	static Vector3D fromBullet(btVector3 v);

	static Vector3D fromOgrePosition(Ogre::Vector3 v);

	static Vector3D fromBulletPosition(btVector3 v);

	static Vector3D fromOgreRotation(Ogre::Quaternion q);

	static Vector3D fromBulletRotation(btQuaternion q);

	static Ogre::Matrix3 fromEulerAngleToRotationMatrix(Vector3D vec);
	
	inline void set(float x, float y, float z) {
		x = x;
		y = y;
		z = z;
	}

	inline void set(const Vector3D& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline void set(const Vector3D&& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline void set(const Vector3D* v) {
		x = v->x;
		y = v->y;
		z = v->z;
	}

	// copy assignment
	inline Vector3D& operator=(const Vector3D& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	// move assignment - not really needed
	inline Vector3D& operator=(const Vector3D&& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	// ** various operations

	// length of the vector
	inline float magnitude() const {
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}

	// vector in the same direction of length 1
	inline Vector3D normalize() const {
		return *this / magnitude();
	}

	//void rotate(Vector3D rot);
	static Ogre::Matrix4 rotationMatrix(Vector3D rotation);
	static Ogre::Matrix4 translationMatrix(Vector3D rotation);
	//Vector3D globalRotation_(Vector3D rot) const;

	static Vector3D crossProduct(Vector3D a, Vector3D b);

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->globalRotation_(angle) == v
	//
	float angle(const Vector3D& v) const;

	// vector subtraction
	inline Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3D operator-=(const Vector3D& v) {
		*this = *this - v;
		return *this;
	}

	// vector addition
	inline Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3D operator+=(const Vector3D& v) {
		*this = *this + v;
		return *this;
	}

	// multiplication by constant (scaling)
	inline Vector3D operator*(float d) const {
		return Vector3D(x * d, y * d, z * d);
	}

	inline Vector3D operator*=(float d) {
		*this = *this * d;
		return *this;
	}

	inline Vector3D operator*(const Vector3D& v) const {
		return Vector3D(x * v.x, y * v.y, z * v.z);
	}

	inline Vector3D operator*=(const Vector3D& v) {
		*this = *this * v;
		return *this;
	}

	// division by constant (scaling)
	inline Vector3D operator/(float d) const {
		return Vector3D(x / d, y / d, z / d);
	}

	inline Vector3D operator/=(float d) {
		*this = *this / d;
		return *this;
	}

	inline Vector3D operator/(const Vector3D& v) const {
		return Vector3D(x / v.x, y / v.y, z / v.z);
	}

	inline Vector3D operator/=(const Vector3D& v) {
		*this = *this / v;
		return *this;
	}

	// scalar multiplication
	// inline float operator *(const Vector3D &d) const {
	// 	return d.x * x + d.y * y + d.z*z;
	// }

};

// needed for printing a value of tyep Vector3D with std::cout.
// The definition is in .cpp
QUACK_ENGINE_PRO_API std::ostream& operator<<(std::ostream& os, const Vector3D& v);
