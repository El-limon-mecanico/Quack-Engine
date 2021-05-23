#include "Button.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "CallBacks.h"


bool Button::init(luabridge::LuaRef parameterTable)
{
	UIElement::init(parameterTable);

	std::string text, tLColor, tRColor, bLColor, bRColor, callback;
	bool correct = true;
	correct &= readVariable<std::string>(parameterTable, "Text", &text);
	correct &= readVariable<std::string>(parameterTable, "TLColor", &tLColor);
	correct &= readVariable<std::string>(parameterTable, "TRColor", &tRColor);
	correct &= readVariable<std::string>(parameterTable, "BLColor", &bLColor);
	correct &= readVariable<std::string>(parameterTable, "BRColor", &bRColor);
	correct &= readVariable<std::string>(parameterTable, "CallBackFunction", &callback);

	if (!correct) return false;

	setCallBackFunction(callback);
	setText(text);
	setTextColor(tLColor, tRColor, bLColor, bRColor);

	return true;
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