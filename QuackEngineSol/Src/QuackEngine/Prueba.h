#pragma once
#include "Component.h"

class Prueba : public Component {
private:
	int valor1;
	int* valor2;
	std::string valor3;

public:
	Prueba(QuackEntity* e = nullptr);
	~Prueba();
	
	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void update() override;

	virtual void onCollisionEnter(QuackEntity* other) override;

	virtual void onCollisionStay(QuackEntity* other) override;

	virtual void onCollisionExit(QuackEntity* other) override;
};