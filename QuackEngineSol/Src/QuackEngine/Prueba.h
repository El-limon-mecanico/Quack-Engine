#pragma once
#include "Component.h"
#include "Transform.h"
#include "checkML.h"

class Prueba : public Component {
private:
	int valor1;
	int* valor2;
	std::string valor3;

public:
	Prueba(QuackEntity* e = nullptr);
	~Prueba();

	static std::string GetName() { return "Prueba"; }
	
	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void update() override;

	virtual void onCollisionEnter(QuackEntity* other , Vector3D point) override;

	virtual void onCollisionStay(QuackEntity* other , Vector3D point) override;

	virtual void onCollisionExit(QuackEntity* other , Vector3D point) override;
};