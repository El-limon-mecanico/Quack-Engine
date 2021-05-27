#pragma once

#include <btBulletDynamicsCommon.h>

class Vector3D;
class BulletQuack;
namespace BtOgre {
	class DynamicsWorld;
};

class Raycast
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