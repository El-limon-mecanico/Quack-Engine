#pragma once
#include "UIElement.h"

namespace CEGUI
{
	class Window;
}


class Button : public UIElement {
public:
	Button() {}

	static std::string GetName() { return "Button"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setButtonEnable(bool active);

	void setCallBackFunction(std::string callBackName);
	void setCallBackFunction(std::function<void()> callBack);
};