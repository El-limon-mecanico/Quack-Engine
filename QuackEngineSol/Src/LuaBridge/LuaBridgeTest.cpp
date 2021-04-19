#include "LuaBridge.h"
#include <iostream>

using namespace luabridge;



void PruebasLua() {	
    lua_State* L = luaL_newstate(); //crea el estado que luego abrirá un archivo (máquina virtual)
	luaL_dofile(L, "Assets/lua/heroe.lua"); //abre el archivo dado
    luabridge::enableExceptions(L); //si no se pone esto peta feo
	
	//luaL_openlibs(L); //no se lo que hace, pero para lo que hacemos no es necesario
    
	//esto es para leer variables tal cual
    LuaRef nameLuaRef = getGlobal(L, "name");
	std::string name = nameLuaRef.cast<std::string>();	
	std::cout << name << "\n";

	//para cargar meta-tablas
    LuaRef characterLuaRef = getGlobal(L, "character").getMetatable();
	try
	{
        std::string name2 = characterLuaRef.rawget("name");
		std::cout << name2 << "\n";
	}
    catch (std::exception e)
    {
        std::cout << "La variable name no es del tipo correcto\n";
    };
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