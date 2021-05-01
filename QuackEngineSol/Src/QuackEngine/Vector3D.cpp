#include "Vector3D.h"
#include <Ogre.h>
#include <LinearMath/btVector3.h>
#include <cassert>


#define PI 3.14159265358979323846264338327950288f

// for printing an object of type Vector3D
std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
	os << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
	return os;
}

Vector3D::Vector3D(Ogre::Vector3 v) :
	x_(v.x),
	y_(v.y),
	z_(v.z)
{

}

Vector3D::Vector3D(btVector3 v) :
	x_(v.x()),
	y_(v.y()),
	z_(v.z())
{
}

Ogre::Vector3 Vector3D::toOgre()
{
	return Ogre::Vector3(x() * 100, y() * 100, z() * 100);
}

btVector3 Vector3D::toBullet()
{
	return btVector3(x() * 100, y() * 100, z() * 100);
}

Vector3D Vector3D::fromOgre(Ogre::Vector3 v)
{
	return Vector3D(v.x / 100, v.y / 100, v.z / 100);
}

Vector3D Vector3D::fromBullet(btVector3 v)
{
	return Vector3D(v.x() / 100, v.y() / 100, v.z() / 100);
}

void Vector3D::rotate(Vector3D rot)
{
	*this = rotation(rot);
}

Vector3D Vector3D::rotation(Vector3D rot) const {

	Vector3D r;

	float degrees = fmod(rot.x(), 360.0f);
	if (degrees > 180.0f) {
		degrees = degrees - 360.0f;
	}
	else if (degrees <= -180.0f) {
		degrees = 360.0f + degrees;
	}

	assert(degrees >= -180.0f && degrees <= 180.0f);

	float angle = degrees * PI / 180.0f;
	float sine = sin(angle);
	float cosine = cos(angle);

	float matrixX[3][3] = { {1,0,0}, {0, cosine, -sine }, {0, sine, cosine } };

	degrees = fmod(rot.y(), 360.0f);
	if (degrees > 180.0f) {
		degrees = degrees - 360.0f;
	}
	else if (degrees <= -180.0f) {
		degrees = 360.0f + degrees;
	}

	assert(degrees >= -180.0f && degrees <= 180.0f);

	angle = degrees * PI / 180.0f;
	sine = sin(angle);
	cosine = cos(angle);

	float matrixY[3][3] = { {cosine,0,sine}, {0, 1, 1 }, {-sine,  0, cosine } };

	degrees = fmod(rot.z(), 360.0f);
	if (degrees > 180.0f) {
		degrees = degrees - 360.0f;
	}
	else if (degrees <= -180.0f) {
		degrees = 360.0f + degrees;
	}

	assert(degrees >= -180.0f && degrees <= 180.0f);

	angle = degrees * PI / 180.0f;
	sine = sin(angle);
	cosine = cos(angle);

	float matrixZ[3][3] = { {cosine,-sine,0}, {sine, cosine, 0 }, {0, 0 ,1 } };

	//r.x_ = matrix[0][0] * x + matrix[0][1] * y;
	//r.y_ = matrix[1][0] * x + matrix[1][1] * y;

	float x = x_;
	float y = y_;
	float z = z_;


	return r;
}

float Vector3D::angle(const Vector3D& v) const {
	float a2 = atan2(v.x(), v.y());
	float a1 = atan2(x_, y_);
	float angle = a1 - a2;
	float K = a1 > a2 ? -2.0f * PI : 2.0f * PI;
	angle = (abs(K + angle) < abs(angle)) ? K + angle : angle;
	return angle * 180.0f / PI;
}
