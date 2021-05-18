#include "Button.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "CallBacks.h"


bool Button::init(luabridge::LuaRef parameterTable)
{
	UIElement::init(parameterTable);
	setText(readVariable<std::string>(parameterTable, "Text"));
	std::string tlColor = readVariable<std::string>(parameterTable, "TLColor");
	std::string tRColor = readVariable<std::string>(parameterTable, "TRColor");
	std::string bLColor = readVariable<std::string>(parameterTable, "BLColor");
	std::string bRColor = readVariable<std::string>(parameterTable, "BRColor");
	setTextColor(tlColor, tRColor, bLColor, bRColor);

	setCallBackFunction(CallBacks::instance()->getMethod(readVariable<std::string>(parameterTable, "CallBackFunction")));

	enable_ = readVariable<bool>(parameterTable, "Enable");

	return true;
}

void Button::setButtonEnable(bool enable)
{
	enable_ = enable;
	element_->setEnabled(enable);
}

void Button::setCallBackFunction(std::string callBackName)
{
	setCallBackFunction(CallBacks::instance()->getMethod(callBackName));
}

void Button::setCallBackFunction(std::function<void()> callBack)
{
	element_->removeAllEvents();
	element_->subscribeEvent(CEGUI::PushButton::EventClicked, callBack);
}