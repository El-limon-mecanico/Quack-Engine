#pragma once
#include "LuaBridge.h"
using namespace luabridge;

LuaRef readLuaFile(std::string file, std::string tableName);