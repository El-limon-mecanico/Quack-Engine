#include "Prueba.h"
#include "LuaManager.h"

//template<typename T>
//extern bool readVariable(LuaRef& table, const std::string& variableName, T& variable);

Prueba::Prueba(QuackEntity* e) : Component(e)
{
	
}

Prueba::~Prueba()
{
}


bool Prueba::init(luabridge::LuaRef parameterTable)
{	
	readVariable<int>(parameterTable, "valor1", valor1);
	valor2 = new int();
	readVariable<int>(parameterTable, "valor2", *valor2);
	readVariable<std::string>(parameterTable, "valor3", valor3);

	std::cout << "\nEstas son las variables que has puesto desde lua: \n";
	std::cout << valor1 << "\n";
	std::cout << *valor2 << "\n";
	std::cout << valor3 << "\n";

	return true;
}

void Prueba::update()
{
	//std::cout << " Update de Prueba\n";
}

