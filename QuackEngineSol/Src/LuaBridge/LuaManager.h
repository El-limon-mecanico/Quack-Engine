#pragma once
#include "LuaBridge.h"
using namespace luabridge;

LuaRef readElementFromFile(lua_State* state, std::string tableName);

lua_State* readFileLua(std::string file);


template<class T>
T readVariable(LuaRef& table, const std::string& variableName)
{
	LuaRef r = NULL;
	try {
		r = table.rawget(variableName);
	}
	catch (...) {
		std::cout << "ERROR: no se ha leido correctamente la variable: " << variableName << "\n";
		return NULL;
	}
	if (r != NULL) {
		try {
			return r.cast<T>();
		}
		catch (...) {
			std::cout << "ERROR: no se pudo convertir la variable " << variableName << " al tipo indicado.\n";
			if (table) {
				try { std::cout << "El valor escrito es: " << table.rawget(variableName).tostring() << "\n"; }
				catch(...) { }
			}
		}
	}
	return NULL;
}