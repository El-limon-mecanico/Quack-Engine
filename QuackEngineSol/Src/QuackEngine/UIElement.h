#pragma once
#include "Component.h"

namespace CEGUI
{
	class Window;
}


class UIElement : public Component {
protected:
	CEGUI::Window* element_;

	bool enable_ = true;

	std::string text_ = "";

	std::pair<float, float> position_;
	std::pair<float, float> size_;

public:
	UIElement() {}
	virtual ~UIElement();

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	virtual void onEnable();

	virtual void onDisable();

	void setText(std::string text);
	std::string getText() { return text_; }

	void setTextFont(std::string font);

	void setTextColor(std::string tLColor, std::string tRColor,
		std::string bLColor, std::string bRColor);

	void setSize(float x, float y);
	void setPosition(float x, float y);

	void setProperty(std::string prop, std::string value);

	std::pair<float, float> getPoisition() { return position_; }
	std::pair<float, float> getSize() { return size_; }
};