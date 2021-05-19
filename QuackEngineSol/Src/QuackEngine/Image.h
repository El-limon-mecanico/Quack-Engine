#pragma once
#include "UIElement.h"

namespace CEGUI
{
	class Window;
}


class Image : public UIElement {
public:
	Image() {}

	static std::string GetName() { return "Image"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void changeImage(std::string name, std::string image = "Missing.jpg");
};