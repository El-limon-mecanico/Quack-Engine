#include "LuaBridge.h"
#include <iostream>

using namespace luabridge;

lua_State* L;

void CargarLua() {
	L = luaL_newstate();
	//luaL_dofile(L, "Assets/heroe.lua");
	//luaL_openlibs(L);
	//lua_pcall(L, 0, 0, 0);
	//LuaRef s = getGlobal(L, "character");
	//LuaRef n = s.getMetatable();
	//std::string luastring = n.getGlobal(L, "name").cast<std::string>();
	//std::cout << luastring << std::endl;
}

std::unordered_map<std::string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef& table)
{
    using namespace luabridge;
    std::unordered_map<std::string, LuaRef> result;
    if (table.isNil()) { return result; }

    auto L = table.state();
    lua_pushglobaltable(L, table); // push table

    lua_pushnil(L);  // push nil, so lua_next removes it from stack and puts (k, v) on stack
    while (lua_next(L, -2) != 0) // -2, because we have table at -1
    {
        result.emplace(LuaRef::fromStack(L, -2), LuaRef::fromStack(L, -1));
        lua_pop(L, 1); // remove value, keep key for lua_next
    }

    lua_pop(L, 1); // pop table
    return result;
}