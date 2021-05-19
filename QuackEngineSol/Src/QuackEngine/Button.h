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


class QUACK_ENGINE_PRO_API Button : public UIElement {
public:
	Button() {}

	static std::string GetName() { return "Button"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });

	void setButtonEnable(bool active);

	void setCallBackFunction(std::string callBackName);
	void setCallBackFunction(std::function<void()> callBack);
};