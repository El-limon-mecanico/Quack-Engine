#include "Vector3D.h"
#include "BtOgre.h"
#include <cassert>


#define PI 3.14159265358979323846264338327950288f

// for printing an object of type Vector3D
std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	return os;
}

Vector3D::Vector3D(Ogre::Vector3 v) :
	x(v.x),
	y(v.y),
	z(v.z)
{

}

Vector3D::Vector3D(btVector3 v) :
	x(v.x()),
	y(v.y()),
	z(v.z())
{
}

Ogre::Vector3 Vector3D::toOgrePosition()
{
	return toOgre(*this * 100);
}

btVector3 Vector3D::toBulletPosition()
{
	return toBullet(*this * 100);
}

Ogre::Quaternion Vector3D::toOgreRotation()
{
	Ogre::Vector3 v(toOgre(*this * PI / 180));
	double yaw = v.y;
	double pitch = v.z;
	double roll = v.x;
	// Abbreviations for the various angular functions
	double cy = cos(pitch * 0.5);
	double sy = sin(pitch * 0.5);
	double cp = cos(yaw * 0.5);
	double sp = sin(yaw * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	Ogre::Quaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;
	return q;
}

btQuaternion Vector3D::toBulletRotation()
{
	Ogre::Vector3 v(toOgre(*this * PI / 180));
	double pitch = v.y;
	double yaw = v.z;
	double roll = v.x;
	// Abbreviations for the various angular functions
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	btQuaternion q;
	q.setW(cr * cp * cy + sr * sp * sy);
	q.setX(sr * cp * cy - cr * sp * sy);
	q.setY(cr * sp * cy + sr * cp * sy);
	q.setZ(cr * cp * sy - sr * sp * cy);
	return q;
}

Ogre::Vector3 Vector3D::toOgre(Vector3D v)
{
	return Ogre::Vector3(v.x, v.y, v.z);
}

btVector3 Vector3D::toBullet(Vector3D v)
{
	return btVector3(v.x, v.y, v.z);
}

Vector3D Vector3D::fromOgre(Ogre::Vector3 v)
{
	return Vector3D(v.x, v.y, v.z);
}

Vector3D Vector3D::fromBullet(btVector3 v)
{
	return Vector3D(v.x(), v.y(), v.z());
}

Vector3D Vector3D::fromOgrePosition(Ogre::Vector3 v)
{
	return fromOgre(v / 100);
}

Vector3D Vector3D::fromBulletPosition(btVector3 v)
{
	return fromBullet(v / 100);
}

Vector3D Vector3D::fromOgreRotation(Ogre::Quaternion q)
{
	Vector3D angles;

	// roll (x-axis globalRotation_)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// yaw (y-axis globalRotation_)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		angles.y = std::copysign(PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = std::asin(sinp);

	// pitch (z-axis globalRotation_)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);


	return angles * 180.0f / PI;
}

Vector3D Vector3D::fromBulletRotation(btQuaternion q)
{
	Vector3D angles;

	//std::cout << q.x << " " << q.y << " " << q.z << " " << q.w << "\n";

	// roll (x-axis globalRotation_)
	double sinr_cosp = 2 * (q.w() * q.x() + q.y() * q.z());
	double cosr_cosp = 1 - 2 * (q.x() * q.x() + q.y() * q.y());
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// yaw (y-axis globalRotation_)
	double sinp = 2 * (q.w() * q.y() - q.z() * q.x());
	if (std::abs(sinp) >= 1)
		angles.y = std::copysign(PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = std::asin(sinp);

	// pitch (z-axis globalRotation_)
	double siny_cosp = 2 * (q.w() * q.z() + q.x() * q.y());
	double cosy_cosp = 1 - 2 * (q.y() * q.y() + q.z() * q.z());
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles * 180.0f / PI;
}

Vector3D Vector3D::globalToLocalPosition(Vector3D globalPosition, Vector3D parentGlobalPosition, Vector3D parentGlobalRotation, Vector3D upParent, Vector3D rightParent, Vector3D forwardParent)
{
	Ogre::Matrix4 rot = rotationMatrix(parentGlobalRotation);
	Ogre::Matrix4 tra = { rightParent.x, upParent.x , forwardParent.x , parentGlobalPosition.x,
							rightParent.y, upParent.y, forwardParent.y , parentGlobalPosition.y,
							rightParent.z, upParent.z, forwardParent.z, parentGlobalPosition.z,
							0, 0, 0, 1
	};

	Ogre::Matrix4 trans = tra * rot;
	Ogre::Vector4f localPosition_ = Ogre::Vector4f(toOgre(globalPosition), 1);

	Ogre::Vector4f ret = trans * localPosition_;

	return  Vector3D(ret.x, ret.y, ret.z);							// TODO MATRICES DE TRANSFORMACIÓN PARA LOS EJES LOCALES
}

Vector3D Vector3D::localToGlobalPosition(Vector3D localPosition, Vector3D parentGlobalPosition, Vector3D parentGlobalRotation)
{
	Ogre::Matrix4 rot = rotationMatrix(parentGlobalRotation);
	Ogre::Matrix4 tra = { 1, 0 , 0 , parentGlobalPosition.x,
							0, 1, 0 , parentGlobalPosition.y,
							0, 0, 1, parentGlobalPosition.z,
							0, 0, 0, 1
	};

	Ogre::Matrix4 trans = tra * rot;
	Ogre::Vector4f localPosition_ = Ogre::Vector4f(toOgre(localPosition), 1);

	Ogre::Vector4f ret = trans * localPosition_;

	return  Vector3D(ret.x, ret.y, ret.z);						// TODO MATRICES DE TRANSFORMACIÓN PARA LOS EJES LOCALES
}

void Vector3D::localToGlobalCoordinates(Vector3D& globalPosition, Vector3D& globalRotation, Vector3D localPosition, Vector3D parentGlobalPosition, Vector3D parentGlobalRotation)
{

	// TODO MATRICES DE TRANSFORMACIÓN PARA LOS EJES LOCALES
}

void Vector3D::globalToLocalCoordinates(Vector3D& localPosition, Vector3D& localRotation, Vector3D globalPosition, Vector3D parentLocalPosition, Vector3D parentLocalRotation)
{

	// TODO MATRICES DE TRANSFORMACIÓN PARA LOS EJES LOCALES
}

//void Vector3D::rotate(Vector3D rot)
//{
//	*this = globalRotation_(rot);
//}

Ogre::Matrix4 Vector3D::rotationMatrix(Vector3D r)
{
	r *= PI / 180;
	Ogre::Matrix4 x, y, z;
	x = { 1,0,0,0,
		 0,cos(r.x), -sin(r.x), 0,
		 0, sin(r.x), cos(r.x), 0,
		 0,0,0,1 };
	y = { cos(r.y), 0,sin(r.y),0,
		 0,1,0,0,
		 -sin(r.y), 0, cos(r.y), 0,
		 0,0,0,1 };
	z = { cos(r.z),-sin(r.z), 0, 0,
		 sin(r.z),cos(r.z), 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1 };

	return (x * y * z);
}

Ogre::Matrix4 Vector3D::translationMatrix(Vector3D rotation)
{
	return Ogre::Matrix4();
}
//
//Vector3D Vector3D::globalRotation_(Vector3D rot) const {
//
//	//Vector3D r;
//
//	//float degrees = fmod(rot.x, 360.0f);
//	//if (degrees > 180.0f) {
//	//	degrees = degrees - 360.0f;
//	//}
//	//else if (degrees <= -180.0f) {
//	//	degrees = 360.0f + degrees;
//	//}
//
//	//assert(degrees >= -180.0f && degrees <= 180.0f);
//
//	//float angle = degrees * PI / 180.0f;
//	//float sine = sin(angle);
//	//float cosine = cos(angle);
//
//	//float matrixX[3][3] = { {1,0,0}, {0, cosine, -sine }, {0, sine, cosine } };
//
//	//degrees = fmod(rot.y(), 360.0f);
//	//if (degrees > 180.0f) {
//	//	degrees = degrees - 360.0f;
//	//}
//	//else if (degrees <= -180.0f) {
//	//	degrees = 360.0f + degrees;
//	//}
//
//	//assert(degrees >= -180.0f && degrees <= 180.0f);
//
//	//angle = degrees * PI / 180.0f;
//	//sine = sin(angle);
//	//cosine = cos(angle);
//
//	//float matrixY[3][3] = { {cosine,0,sine}, {0, 1, 1 }, {-sine,  0, cosine } };
//
//	//degrees = fmod(rot.z(), 360.0f);
//	//if (degrees > 180.0f) {
//	//	degrees = degrees - 360.0f;
//	//}
//	//else if (degrees <= -180.0f) {
//	//	degrees = 360.0f + degrees;
//	//}
//
//	//assert(degrees >= -180.0f && degrees <= 180.0f);
//
//	//angle = degrees * PI / 180.0f;
//	//sine = sin(angle);
//	//cosine = cos(angle);
//
//	//float matrixZ[3][3] = { {cosine,-sine,0}, {sine, cosine, 0 }, {0, 0 ,1 } };
//
//	////r.x = matrix[0][0] * x + matrix[0][1] * y;
//	////r.y = matrix[1][0] * x + matrix[1][1] * y;
//
//	//float x = x;
//	//float y = y;
//	//float z = z;
//
//
//	//return r;
//
//	return Vector3D();
//}

Vector3D Vector3D::crossProduct(Vector3D a, Vector3D b)
{
	return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

float Vector3D::angle(const Vector3D& v) const {
	float a2 = atan2(v.x, v.y);
	float a1 = atan2(x, y);
	float angle = a1 - a2;
	float K = a1 > a2 ? -2.0f * PI : 2.0f * PI;
	angle = (abs(K + angle) < abs(angle)) ? K + angle : angle;
	return angle * 180.0f / PI;
}
