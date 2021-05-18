#pragma once
#include "UIElement.h"

namespace CEGUI
{
	class Window;
}


class Text : public UIElement {
public:
	Text() {}

	static std::string GetName() { return "Text"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setBackground(bool set);

	void setBorder(bool set);
};