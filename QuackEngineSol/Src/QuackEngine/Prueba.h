#pragma once
#include "Component.h"
#include "checkML.h"

class Prueba : public Component {
private:
	int valor1;
	int* valor2;
	std::string valor3;
	float scalealgo = 0;
	bool mouseVisinility_ = true;

public:
	Prueba(QuackEntity* e = nullptr);
	~Prueba();

	static std::string GetName() { return "Prueba"; }
	
	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void start() override;

	virtual void fixedUpdate() override;

	virtual void update() override;

	virtual void onCollisionEnter(QuackEntity* other , Vector3D point) override;
	virtual void onCollisionEnter(QuackEntity* other, Vector3D point, Vector3D normal) override;

	virtual void onCollisionStay(QuackEntity* other , Vector3D point) override;

	virtual void onCollisionExit(QuackEntity* other , Vector3D point) override;

	virtual void onTriggerEnter(QuackEntity* other, Vector3D point) override;

	virtual void onTriggerStay(QuackEntity* other, Vector3D point) override;

	virtual void onTriggerExit(QuackEntity* other, Vector3D point) override;
};