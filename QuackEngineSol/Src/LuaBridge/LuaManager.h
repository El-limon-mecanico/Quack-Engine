#pragma once
#include "LuaBridge.h"
using namespace luabridge;

LuaRef readElementFromFile(lua_State* state, std::string tableName);

lua_State* readFileLua(std::string file);
//
//template<class T>
//T readVariable(LuaRef& table, const std::string& variableName)
//{
//	LuaRef r = NULL;
//	try {
//		r = table.rawget(variableName);
//		if (r != NULL && !r.isRefNil()) {
//			try {
//				return r.cast<T>();
//			}
//			catch (...) {
//				std::cout << "ERROR: no se pudo convertir la variable " << variableName << " al tipo indicado.\n";
//				if (table) {
//					try { std::cout << "El valor escrito es: " << table.rawget(variableName).tostring() << "\n"; }
//					catch(...) { }
//				}
//			}
//		}
//	}
//	catch (...) {
//		std::cout << "ERROR: no se ha leido correctamente la variable: " << variableName << "\n";
//	}
//	if (detect_string::detect<T>)
//	{
//		T* t = new T();
//		return *t;
//	}
//	return NULL;
//}

template<class T>
bool readVariable(LuaRef& table, const std::string& variableName, const T* variable)
{
	LuaRef r = NULL;
	try {
		r = table.rawget(variableName);
		if (r != NULL && !r.isRefNil()) {
			try {
				*variable = r.cast<T>();
				return true;				// lectura correcta
			}
			catch (...) {
				std::cout << "ERROR: no se pudo convertir la variable " << variableName << " al tipo indicado.\n";
				if (table) {
					try { std::cout << "El valor escrito es: " << table.rawget(variableName).tostring() << "\n"; }
					catch(...) { }
				}
			}
		}
		else std::cout << "ERROR: no se ha leido correctamente la variable: " << variableName << "\n";
	}
	catch (...) {
		std::cout << "ERROR: no se ha leido correctamente la variable: " << variableName << "\n";
	}
	return false;							// lectura incorrecta, variable sin inicializar
}