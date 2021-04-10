#pragma once
#include "Component.h"

class Prueba : public Component {
private:
	int valor1;
	int* valor2;
	std::string valor3;

public:
	Prueba(Entity* e = nullptr) : Component(e) {}
	~Prueba() {}

	//TODO cambiar a una tabla de lua
	bool init(const std::unordered_map<std::string, std::string>& parameterTable);
};