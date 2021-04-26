#include "Prueba.h"


Prueba::Prueba(QuackEntity* e) : Component(e)
{
	
}

Prueba::~Prueba()
{
}

bool Prueba::init(luabridge::LuaRef parameterTable)
{
	enableExceptions(parameterTable);

	try
	{
		valor1 = parameterTable.rawget("valor1");
	}
	catch (std::exception e)
	{
		std::cout << "ERROR: La variable valor1 no existo o no es del tipo correcto\n";
	}
	
	try
	{
		int val = parameterTable.rawget("valor2");
		valor2 = new int(val);
	}
	catch (std::exception e)
	{
		std::cout << "ERROR: La variable valor2 no existe no es del tipo correcto\n";
	}

	std::string aux = parameterTable.rawget("valor3");
	valor3 = aux;


	std::cout << "\nEstas son las variables que has puesto desde lua: \n";
	std::cout << valor1 << "\n";
	if(valor2 != nullptr)std::cout << *valor2 << "\n";
	std::cout << valor3 << "\n";
	return true;
}

void Prueba::update()
{
	std::cout << " Update de Prueba\n";
}

