#include <iostream>
#include <CEGUI\CEGUI.h>
#include <CEGUI\ScriptModules\Lua\CEGUILua.h>
void CEGUI_Init()
{
	std::cout << "Aqui deberia estar cargando CEGUI\n";
	CEGUI::LuaFunctor;
}