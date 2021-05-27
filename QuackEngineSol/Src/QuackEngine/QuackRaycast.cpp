#include "QuackRaycast.h"
#include "Vector3D.h"
#include "Raycast.h"

QuackRaycast::QuackRaycast(Vector3D from, Vector3D to)
{
	raycast = new Raycast(from, to);
}

QuackRaycast::~QuackRaycast()
{
	delete raycast;
	raycast = nullptr;
}

bool QuackRaycast::hasHit() const {
	return raycast->hasHit();
}

float QuackRaycast::getLength() {
	return raycast->getLength();
}

Vector3D QuackRaycast::getNormal() {
	return raycast->getNormal();
}