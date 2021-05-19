#include "Image.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

bool Image::init(luabridge::LuaRef parameterTable)
{
    UIElement::init(parameterTable);
    std::string name = readVariable<std::string>(parameterTable, "Name");
    std::string image = readVariable<std::string>(parameterTable, "Image");
    if (!CEGUI::ImageManager::getSingleton().isDefined(name))
        CEGUI::ImageManager::getSingleton().addFromImageFile(name, image);

    setBackground(readVariable<bool>(parameterTable, "Background"));
    setBorder(readVariable<bool>(parameterTable, "Border"));
	
    element_->setProperty("Image", name);
    return true;
}

void Image::changeImage(std::string name, std::string image)
{
    if (!CEGUI::ImageManager::getSingleton().isDefined(name))
        CEGUI::ImageManager::getSingleton().addFromImageFile(name, image);
    element_->setProperty("Image", name);
}
