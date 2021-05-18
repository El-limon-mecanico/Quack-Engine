#pragma once
#include "Component.h"

namespace CEGUI
{
	class Window;
}


class Button : public Component {
private:
	CEGUI::Window* button_;

	bool visible_;
	bool active_;

	std::string text_;

	std::pair<float, float> position_;
	std::pair<float, float> size_;

public:
	Button() {}
	~Button();

	static std::string GetName() { return "Button"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	virtual void onEnable();

	virtual void onDisable();

	void setActive(bool active);

	void setText(std::string text);

	void setTextFont(std::string font);

	void setCallBackFunction(std::string callBackName);
	void setCallBackFunction(std::function<void()> callBack);

	void setSize(float x, float y);
	void setPosition(float x, float y);

	std::pair<float, float> getPoisition() { return position_; }
	std::pair<float, float> getSize() { return size_; }
};