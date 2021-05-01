// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

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
}

class btVector3;
class btQuaternion;

class Vector3D {
private:
	float x_;  // First coordinate
	float y_;  // Second coordinate
	float z_;  // Third coordinate
public:

	// various constructors
	Vector3D() noexcept :
		x_(), y_(), z_() {
	}

	Vector3D(const Vector3D& v) :
		x_(v.x()), y_(v.y()), z_(v.z()) {
	}

	Vector3D(Vector3D&& v) :
		x_(v.x()), y_(v.y()), z_(v.z()) {
	}

	Vector3D(const Vector3D* v) :
		x_(v->x()), y_(v->y()), z_(v->z()) {
	}

	Vector3D(float x, float y, float z) :
		x_(x), y_(y), z_(z) {
	}

	Vector3D(Ogre::Vector3 v);

	Vector3D(btVector3 v);

	~Vector3D() {
	}

	// various getters
	inline float x() const {
		return x_;
	}

	inline float y() const {
		return y_;
	}

	inline float z() const {
		return z_;
	}

	Ogre::Vector3 toOgrePosition();

	btVector3 toBulletPosition();

	Ogre::Quaternion toOgreRotation();

	btQuaternion toBulletRotation();

	static Ogre::Vector3 toOgre(Vector3D v);

	static btVector3 toBullet(Vector3D v);

	static Vector3D fromOgre(Ogre::Vector3 v);

	static Vector3D fromBullet(btVector3 v);

	static Vector3D fromOgrePosition(Ogre::Vector3 v);

	static Vector3D fromBulletPosition(btVector3 v);

	static Vector3D fromOgreRotation(Ogre::Quaternion q);

	static Vector3D fromBulletRotation(btQuaternion q);



	// various setters
	inline void setX(float x) {
		x_ = x;
	}

	inline void setY(float y) {
		y_ = y;
	}

	inline void setZ(float z) {
		z_ = z;
	}

	inline void set(float x, float y, float z) {
		x_ = x;
		y_ = y;
		z_ = z;
	}

	inline void set(const Vector3D& v) {
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
	}

	inline void set(const Vector3D&& v) {
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
	}

	inline void set(const Vector3D* v) {
		x_ = v->x_;
		y_ = v->y_;
		z_ = v->z_;
	}

	// copy assignment
	inline Vector3D& operator=(const Vector3D& v) {
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		return *this;
	}

	// move assignment - not really needed
	inline Vector3D& operator=(const Vector3D&& v) {
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		return *this;
	}

	// ** various operations

	// length of the vector
	inline float magnitude() const {
		return sqrtf(powf(x_, 2) + powf(y_, 2) + powf(z_, 2));
	}

	// vector in the same direction of length 1
	inline Vector3D normalize() const {
		return *this / magnitude();
	}

	void rotate(Vector3D rot);

	Vector3D rotation(Vector3D rot) const;

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->rotation(angle) == v
	//
	float angle(const Vector3D& v) const;

	// vector subtraction
	inline Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x_ - v.x_, y_ - v.y_, z_ + v.z_);
	}

	inline Vector3D operator-=(const Vector3D& v) {
		*this = *this - v;
		return *this;
	}

	// vector addition
	inline Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
	}

	inline Vector3D operator+=(const Vector3D& v) {
		*this = *this + v;
		return *this;
	}

	// multiplication by constant (scaling)
	inline Vector3D operator*(float d) const {
		return Vector3D(x_ * d, y_ * d, z_ * d);
	}

	// division by constant (scaling)
	inline Vector3D operator/(float d) const {
		return Vector3D(x_ / d, y_ / d, z_ / d);
	}

	// scalar multiplication
	// inline float operator *(const Vector3D &d) const {
	// 	return d.x_ * x_ + d.y_ * y_ + d.z_*z_;
	// }

};

// needed for printing a value of tyep Vector3D with std::cout.
// The definition is in .cpp
std::ostream& operator<<(std::ostream& os, const Vector3D& v);
