#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include "BulletQuack.h"
#include "BtOgre.h"
#include "Vector3D.h"

//class Vector3D;
//class btVector3;
//class btCollisionWorld {
//	struct RayResultCallback;
//	struct ClosestRayResultCallback;
//};
//class btDynamicsWorld;

class QUACK_ENGINE_PRO_API Raycast
{
private:
	btVector3* from_ = nullptr, * to_ = nullptr;
	btCollisionWorld::ClosestRayResultCallback* res = nullptr;

public:
	Raycast(Vector3D from, Vector3D to);
	~Raycast();
	bool hasHit() const;
	float getLength();
	Vector3D getNormal();
};