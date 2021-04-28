#include "LuaBridge.h"
using namespace luabridge;

LuaRef readElementFromFile(lua_State* state, std::string tableName)
{
	LuaRef aux = getGlobal(state, tableName.c_str());
	return aux;
}

lua_State* readFileLua(std::string file)
{
	lua_State* state = luaL_newstate();
	std::string path = "Assets/lua/" + file;
	luaL_dofile(state, path.c_str());
	return state;
}