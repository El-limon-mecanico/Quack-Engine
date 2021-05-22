#include "Image.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

bool Image::init(luabridge::LuaRef parameterTable)
{
    UIElement::init(parameterTable);

    std::string name, image;
    bool background, border;
    bool correct = true;
    correct &= readVariable<std::string>(parameterTable, "Name", &name);
    correct &= readVariable<std::string>(parameterTable, "Image", &image);
    correct &= readVariable<bool>(parameterTable, "Background", &background);
    correct &= readVariable<bool>(parameterTable, "Border", &border);

    if (!correct) return false;

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