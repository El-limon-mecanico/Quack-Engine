#pragma once
#include "Component.h"
#include "checkML.h"

class Prueba2 : public Component {
private:
	int valor1;
	int* valor2;
	std::string valor3;

	float algo = 0;

public:
	Prueba2(QuackEntity* e = nullptr);
	~Prueba2();

	static std::string GetName() { return "Prueba2"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr }) override;

	virtual void update() override;

};
