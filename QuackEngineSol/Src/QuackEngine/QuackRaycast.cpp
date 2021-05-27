#include "QuackRaycast.h"

QuackRaycast::QuackRaycast(Vector3D from, Vector3D to)
{
	raycast = new Raycast(from, to);
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