#include "LuaBridge.h"
using namespace luabridge;

LuaRef readLuaFile(std::string file, std::string tableName)
{
	lua_State* state = luaL_newstate();
	std::string path = "Assets/lua/" + file;
	luaL_dofile(state, path.c_str());
	enableExceptions(state);
	try
	{
		LuaRef aux = getGlobal(state, tableName.c_str()).getMetatable();
		std::cout << "El fichero " + file << " se ha abierto bien\n";
		return aux;
	}
	catch (std::exception e)
	{
		std::cout << "No se ha podido cargar el archivo " << file;
		std::cout << " revisa que esté en Asstets/lua/\n";
	}
}