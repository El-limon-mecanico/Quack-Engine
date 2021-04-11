#pragma once
#include "Component.h"

class Prueba : public Component {
private:
	int valor1;
	int* valor2;
	std::string valor3;

public:
	Prueba(Entity* e = nullptr);
	~Prueba();

	//TODO cambiar a una tabla de lua
	virtual bool init(const std::unordered_map<std::string, luabridge::LuaRef>& parameterTable);
};