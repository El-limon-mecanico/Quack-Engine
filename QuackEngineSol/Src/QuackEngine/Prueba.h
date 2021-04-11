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
	
	virtual bool init(luabridge::LuaRef parameterTable);
	
};