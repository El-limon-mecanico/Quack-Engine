#include "Prueba.h"


Prueba::Prueba(Entity* e): Component(e)
{
	//cargar desde el componente desde lua para probar

	//se deberia linkear este componente a la entidad (aun no existe)
}

Prueba::~Prueba()
{
}

bool Prueba::init(const std::unordered_map<std::string, luabridge::LuaRef>& parameterTable)
{
	//TODO cambiar a gestion de tabla de lua
	//valor1 = parameterTable.at("valor1");
	//valor2 = parameterTable.at("valor2");
	//valor3 = parameterTable.at("valor3");

	return true;
}
