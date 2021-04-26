#pragma once
#include "LuaBridge.h"
using namespace luabridge;

LuaRef readElementFromFile(lua_State* state, std::string tableName);

lua_State* readFileLua(std::string file);

template<class T>
void readVariable(LuaRef& table, const std::string& variableName, T& variable)
{
	try
	{
		variable = table.rawget(variableName).cast<T>();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR: no se ha cargado correctamente la variable: " << variableName << "\n";
		std::cout << "El valor escrito es: " << table.rawget(variableName).tostring() << "\n";
	}
}