#pragma once
#include "Component.h"
#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

namespace CEGUI
{
	class Window;
}


class QUACK_ENGINE_PRO_API UIElement : public Component {
protected:
	CEGUI::Window* element_;

	bool enable_ = true;

	std::string text_ = "";

	std::pair<float, float> position_;
	std::pair<float, float> size_;

public:
	UIElement() {}
	virtual ~UIElement();

	static void addScheme(std::string scheme);

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });
	bool init(std::pair<float, float> pos, std::pair<float, float> size, bool active, std::string name, std::string style);

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

	void setBackground(bool set);

	void setBorder(bool set);

	std::pair<float, float> getPoisition() { return position_; }
	std::pair<float, float> getSize() { return size_; }
};