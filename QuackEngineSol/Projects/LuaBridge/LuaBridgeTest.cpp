#include "LuaBridge.h"
#include <iostream>

using namespace luabridge;

void CargarLua() {
	lua_State* l = luaL_newstate();
	luaL_dofile(l, "Assets/heroe.lua");
	luaL_openlibs(l);
	lua_pcall(l, 0, 0, 0);
	LuaRef s = getGlobal(l, "character");
	LuaRef n = s.getMetatable();
	std::string luastring = n.getGlobal(l, "name").cast<std::string>();
	std::cout << luastring << std::endl;
}