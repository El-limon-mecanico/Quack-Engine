#pragma once
#include "Component.h"

namespace CEGUI
{
	class Window;
}


class Text : public Component {
private:
	CEGUI::Window* text_;

public:
	Text() {}
	~Text() {}

	static std::string GetName() { return "Text"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	virtual void start() {}

	virtual void onEnable() {}

	virtual void onDisable() {}
};

