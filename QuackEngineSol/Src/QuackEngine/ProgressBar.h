#pragma once
#include "UIElement.h"
#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

namespace CEGUI
{
	class ProgressBar;
}


class QUACK_ENGINE_PRO_API ProgressBar : public UIElement {
private:
	CEGUI::ProgressBar* bar_;
public:
	ProgressBar() {}
	ProgressBar(std::string name, std::string image, bool background, bool border, bool active,
		std::pair<float, float> pos, std::pair<float, float> size, std::string style) {
		UIElement::init(pos, size, active, name, style);
	};

	static std::string GetName() { return "ProgressBar"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setProgress(float progress);

	void addProgress(float progress);

	float getProgress();
};