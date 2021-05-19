#include "Text.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

bool Text::init(luabridge::LuaRef parameterTable)
{
    UIElement::init(parameterTable);
    setText(readVariable<std::string>(parameterTable, "Text"));
    std::string tlColor = readVariable<std::string>(parameterTable, "TLColor");
    std::string tRColor = readVariable<std::string>(parameterTable, "TRColor");
    std::string bLColor = readVariable<std::string>(parameterTable, "BLColor");
    std::string bRColor = readVariable<std::string>(parameterTable, "BRColor");
    setTextColor(tlColor, tRColor, bLColor, bRColor);

    setBackground(readVariable<bool>(parameterTable, "Background"));
    setBorder(readVariable<bool>(parameterTable, "Border"));

    return true;
}