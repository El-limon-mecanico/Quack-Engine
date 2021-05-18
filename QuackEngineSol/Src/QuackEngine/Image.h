#pragma once
#include "Component.h"

namespace CEGUI
{
	class Window;
}


class Image : public Component {
private:
	CEGUI::Window* image_;

public:
	Image() {}
	~Image() {}

	static std::string GetName() { return "Image"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	virtual void start() {}

	virtual void onEnable() {}

	virtual void onDisable() {}
};
