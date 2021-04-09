#include <iostream>
#include "LuaBridge.h"

using namespace luabridge;

int main()
{
	lua_State* l = luaL_newstate();
	//luaL_dofile(l, "heroe.lua");
	//luaL_openlibs(l);
	//lua_pcall(l, 0, 0, 0);
	//LuaRef s = getGlobal(l, "teststring");
	//LuaRef n = getGlobal(l, "number");
	//std::string luastring = s.cast<std::string>();
	//int answer = n.cast<int>();
	//std::cout << luastring << std::endl;
	//std::cout << "and here's our number:" << answer << std::endl;
	return 0;
}