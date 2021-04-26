#pragma once
#include "LuaBridge.h"
using namespace luabridge;

LuaRef readElementFromFile(lua_State* state, std::string tableName);

lua_State* readFileLua(std::string file);