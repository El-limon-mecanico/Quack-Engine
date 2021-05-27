#pragma once
#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include "Raycast.h"
#include "Vector3D.h"

class QUACK_ENGINE_PRO_API QuackRaycast {
private:
	Raycast* raycast = nullptr;

public:
	QuackRaycast(Vector3D from, Vector3D to);
	~QuackRaycast() { delete raycast; raycast = nullptr; }
	bool hasHit() const;
	float getLength();
	Vector3D getNormal();
};