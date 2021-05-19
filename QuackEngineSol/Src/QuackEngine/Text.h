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


class QUACK_ENGINE_PRO_API Text : public UIElement {
public:
	Text() {}

	static std::string GetName() { return "Text"; }

	virtual bool init(luabridge::LuaRef parameterTable = { nullptr });
};