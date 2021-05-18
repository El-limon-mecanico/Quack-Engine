#include "UIElement.h"
#include <CEGUIQuack.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

UIElement::~UIElement()
{
	CEGUIQuack::Instance()->removeWidget(element_);
	element_ = nullptr;
}

void UIElement::addScheme(std::string scheme)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(scheme);
}

bool UIElement::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	LuaRef size = readVariable<LuaRef>(parameterTable, "Size");

	element_ = CEGUIQuack::Instance()->createWidget(readVariable<std::string>(parameterTable, "Style"),
		readVariable<std::string>(parameterTable, "Name"));

	setPosition(pos[1], pos[2]);

	setSize(size[1], size[2]);

	setEnable(readVariable<bool>(parameterTable, "Active"));

	return true;
}

void UIElement::onEnable()
{
	element_->setVisible(true);
	element_->setEnabled(enable_);
}

void UIElement::onDisable()
{
	element_->setVisible(false);
}

void UIElement::setText(std::string text)
{
	text_ = text;
	element_->setText(text);
}

void UIElement::setTextFont(std::string font)
{
	element_->setFont(font);
}

void UIElement::setTextColor(std::string tLColor, std::string tRColor, std::string bLColor, std::string bRColor)
{
	std::string color = "tl:" + tLColor + "tr:" + tRColor + "bl:" + bLColor + "br:" + bRColor;
	if (element_->isPropertyPresent("TextColours"))
		element_->setProperty("TextColours", color);
}

void UIElement::setSize(float x, float y)
{
	size_ = { x,y };
	CEGUI::UDim x_ = CEGUI::UDim(0, x);
	CEGUI::UDim y_ = CEGUI::UDim(0, y);
	element_->setSize({ x_,y_ });
}

void UIElement::setPosition(float x, float y)
{
	position_ = { x,y };
	CEGUI::UDim x_ = CEGUI::UDim(x, 0);
	CEGUI::UDim y_ = CEGUI::UDim(y, 0);

	element_->setPosition({ x_,y_ });
}

void UIElement::setProperty(std::string prop, std::string value)
{
	if (element_->isPropertyPresent(prop))
		element_->setProperty(prop, value);
	else
		std::cout << prop << " no es una propiedad que exista dentro del style cargado\n";
}
