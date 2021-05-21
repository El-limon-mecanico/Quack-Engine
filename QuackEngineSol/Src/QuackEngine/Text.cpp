#include "Text.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

bool Text::init(luabridge::LuaRef parameterTable)
{
    UIElement::init(parameterTable);

    std::string text, tLColor, tRColor, bLColor, bRColor;
    bool background = true, border = true;
    bool correct = true;
    correct &= readVariable<std::string>(parameterTable, "Text", &text);
    correct &= readVariable<std::string>(parameterTable, "TLColor", &tLColor);
    correct &= readVariable<std::string>(parameterTable, "TRColor", &tRColor);
    correct &= readVariable<std::string>(parameterTable, "BLColor", &bLColor);
    correct &= readVariable<std::string>(parameterTable, "BRColor", &bRColor);
    correct &= readVariable<bool>(parameterTable, "Background", &background);
    correct &= readVariable<bool>(parameterTable, "Border", &border);

    if (!correct) return false;

    setText(text);
    setTextColor(tLColor, tRColor, bLColor, bRColor);
    setBackground(background);
    setBorder(border);

    return true;
}