#include "Raycast.h"
#include "BulletQuack.h"
#include "BtOgre.h"
#include "../QuackEngine/Vector3D.h"

Raycast::Raycast(Vector3D from, Vector3D to)
{
	from_ = new btVector3(from.x, from.y, from.z);
	to_ = new btVector3(to.x, to.y, to.z);

	res = new btCollisionWorld::ClosestRayResultCallback(*from_, *to_);

	BulletQuack::Instance()->getWorld()->getBtWorld()->rayTest(*from_, *to_, *res);
}
Raycast::~Raycast()
{
	delete from_;	from_ = nullptr;
	delete to_;		to_ = nullptr;
	delete res;		res = nullptr;
}

bool Raycast::hasHit() const {
	return res->hasHit();
}

float Raycast::getLength() {
	return (res->m_hitPointWorld - *from_).length();
}

Vector3D Raycast::getNormal() {
	return res->m_hitNormalWorld;
}