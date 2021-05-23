#include "LuaBridge.h"
using namespace luabridge;

const std::string assets_path = "../../../Assets";

LuaRef readElementFromFile(lua_State* state, std::string tableName)
{
	LuaRef aux = getGlobal(state, tableName.c_str());
	return aux;
}

lua_State* readFileLua(std::string file)
{
	lua_State* state = luaL_newstate();
	std::string path = assets_path + "/lua/" + file;
	
	int aux = luaL_dofile(state, path.c_str());
	if (aux != 0) {
		std::string msg = "ERROR: Calling luaL_dofile resulted in failure. Error: ";
		std::string error = lua_tostring(state, -1);
		throw(msg + error);
	}

	return state;
}