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
	class Window;
}


class QUACK_ENGINE_PRO_API Image : public UIElement {
private:
	void initImage(std::string name, std::string image, bool background, bool border);
public:
	Image() {}
	Image(std::string name, std::string image, bool background, bool border, bool active,
		  std::pair<float,float> pos, std::pair<float, float> size, std::string style) {
		UIElement::init(pos, size, active, name, style);
		initImage(name, image, background, border); 
	};

	static std::string GetName() { return "Image"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void changeImage(std::string name, std::string image = "Missing.jpg");
};