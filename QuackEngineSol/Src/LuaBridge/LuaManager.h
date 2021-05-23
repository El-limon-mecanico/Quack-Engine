#pragma once
#include "LuaBridge.h"
using namespace luabridge;

LuaRef readElementFromFile(lua_State* state, std::string tableName);

lua_State* readFileLua(std::string file);

template<typename T>
inline void __readVariable_asig__(LuaRef& r, T* variable) {
	*variable = r.cast<T>();
}

template<>
inline void __readVariable_asig__<std::string>(LuaRef& r, std::string* variable) {
	std::string casted = r.cast<std::string>();
	variable->reserve(sizeof(casted));
	*variable = casted;
}

template<typename T>
inline bool __readVariable_checkforLuaRefNull__() {
	return true;
}

template<>
inline bool __readVariable_checkforLuaRefNull__<LuaRef>() {
	return false;
}

template<typename T>
inline bool readVariable(LuaRef& table, const std::string& variableName, T* variable)
{
	std::cout << "	Variable " << variableName << "\n";
	if (!variable || variable == nullptr) {
		std::cout << "ERROR: No se ha reservado espacio en memoria para la variable. La variable debe estar inicializada en memoria para poder llamar a readVariable sin errores.\n";
		return false;
	}

	LuaRef r = NULL;
	try {
		r = table.rawget(variableName);
		if (!r.isRefNil()) {
			try {
				__readVariable_asig__(r, variable);
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
		else {
			std::cout << "	WARNING: no se ha indicado el valor de la variable: " << variableName << ". Se usara el valor por defecto.\n";
			return __readVariable_checkforLuaRefNull__<T>();
		}
	}
	catch (...) {
		std::cout << "ERROR: no se ha leido correctamente la variable: " << variableName << "\n";
	}
	return false;							// lectura incorrecta, variable sin inicializar
}