#pragma once
#include <unordered_map>
#include <LuaBridge.h>

void PruebasLua();

// function that converts a Lua table into an unordered_map of LuaRefs.
// These LuaRefs need to be casted before use by calling lua_to*type*(LuaRef foo)
std::unordered_map<std::string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef& table);