#pragma once
#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

class Raycast;
class Vector3D;

class QUACK_ENGINE_PRO_API QuackRaycast {
private:
	Raycast* raycast = nullptr;

public:
	QuackRaycast(Vector3D from, Vector3D to);
	~QuackRaycast();
	bool hasHit() const;
	float getLength();
	Vector3D getNormal();
};