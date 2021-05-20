#include "Image.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

bool Image::init(luabridge::LuaRef parameterTable)
{
    UIElement::init(parameterTable);
    std::string name = readVariable<std::string>(parameterTable, "Name");
    std::string image = readVariable<std::string>(parameterTable, "Image");
    bool background = readVariable<bool>(parameterTable, "Background");
    bool border = readVariable<bool>(parameterTable, "Border");

    initImage(name, image, background, border);
    return true;
}

void Image::changeImage(std::string name, std::string image)
{
    if (!CEGUI::ImageManager::getSingleton().isDefined(name))
        CEGUI::ImageManager::getSingleton().addFromImageFile(name, image);
    element_->setProperty("Image", name);
}

void Image::initImage(std::string name, std::string image, bool background, bool border) {
    setBackground(background);
    setBorder(border);
    if (!CEGUI::ImageManager::getSingleton().isDefined(name))
        CEGUI::ImageManager::getSingleton().addFromImageFile(name, image);
    element_->setProperty("Image", name);
    element_->setZOrderingEnabled(false); //para que no puedas interactuar con la imagen
}