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

	Vector3D(const Vector3D &v) :
			x_(v.x()), y_(v.y()), z_(v.z()) {
	}

	Vector3D(Vector3D &&v) :
			x_(v.x()), y_(v.y()), z_(v.z()) {
	}

	Vector3D(const Vector3D *v) :
			x_(v->x()), y_(v->y()), z_(v->z()) {
	}

	Vector3D(float x, float y, float z) :
			x_(x), y_(y), z_(z) {
	}

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
	inline Vector3D getForOgre(){
		return *this*100; //comprobar el numerito y palante
	}
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

	inline void set(const Vector3D &v) {
		x_ = v.x_;
		y_ = v.y_;
        z_  =v.z_;
	}

	inline void set(const Vector3D &&v) {
		x_ = v.x_;
		y_ = v.y_;
        z_ = v.z_;
	}

	inline void set(const Vector3D *v) {
		x_ = v->x_;
		y_ = v->y_;
        z_ = v->z_;
	}

	// copy assignment
	inline Vector3D& operator=(const Vector3D &v) {
		x_ = v.x_;
		y_ = v.y_;
        z_ = v.z_;
		return *this;
	}

	// move assignment - not really needed
	inline Vector3D& operator=(const Vector3D &&v) {
		x_ = v.x_;
		y_ = v.y_;
        z_ = v.z_;
		return *this;
	}

	// ** various operations

	// length of the vector
	inline float magnitude() const {
		return sqrtf(powf(x_, 2) + powf(y_, 2)+powf(z_,2));
	}

	// vector in the same direction of length 1
	inline Vector3D normalize() const {
		return *this / magnitude();
	}

	// counter clockwise rotation in a normal coordinate system, and
	// it is clockwise rotation if we work with a coordinate system
	// in which the vertical axe is flipped (it is like a mirror over
	// the horizontal axe)-- which the case when working with the SDL.
	//
	Vector3D rotate(float degrees) const;

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->rotate(angle) == v
	//
	float angle(const Vector3D &v) const;

	// vector subtraction
	inline Vector3D operator-(const Vector3D &v) const {
		return Vector3D(x_ - v.x_, y_ - v.y_, z_ +v.z_);
	}

	// vector addition
	inline Vector3D operator+(const Vector3D &v) const {
		return Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
	}

	// multiplication by constant (scaling)
	inline Vector3D operator*(float d) const {
		return Vector3D(x_ * d, y_ * d, z_*d);
	}

	// division by constant (scaling)
	inline Vector3D operator/(float d) const {
		return Vector3D(x_ / d, y_ / d, z_/d);
	}

	// scalar multiplication
	// inline float operator *(const Vector3D &d) const {
	// 	return d.x_ * x_ + d.y_ * y_ + d.z_*z_;
	// }

};

// needed for printing a value of tyep Vector3D with std::cout.
// The definition is in .cpp
std::ostream& operator<<(std::ostream &os, const Vector3D &v);
