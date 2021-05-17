#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <memory>
#include <assert.h>
#include <SDL_scancode.h>
#include "SDL_mouse.h"

namespace CEGUI {
	enum MouseButton;
}

union SDL_Event;

enum Axis {
	Horizontal,
	Vertical
};

class QUACK_ENGINE_PRO_API InputManager
{
private:
	static std::unique_ptr<InputManager> instance_;

	struct MousePositionAbsolute
	{
		int x = 0;
		int y = 0;
	} mousePositionAbsolute_;

	struct MousePositionRelative
	{
		float x = 0;
		float y = 0;
	} mousePositionRelative_;

	struct MouseButtons {
		bool leftDown = false;
		bool middleDown = false;
		bool rightDown = false;
	}mouseButtons_;

	struct MouseWheel {
		int x = 0;
		int y = 0;
	}mouseWheel_;

	void injectInputCegui(SDL_Event event);

	CEGUI::MouseButton sdlMouseButtonToCegui(Uint8 buttonSDL);

	Uint32 sdlKeyToCegui(SDL_Scancode sdlKeycode);

public:

	static bool Init();
	static InputManager* Instance();

	InputManager() {}
	~InputManager();

	void ManageInput(SDL_Event event);

	void MouseWheelChange(int coordinate, int value);

	MousePositionAbsolute getMousePositionAbsolute();

	MousePositionRelative getMousePositionRelative();

	MouseButtons getMouseButtons();

	MouseWheel getMouseWheel();

	bool isKeyDown(SDL_Scancode code);

	int getAxis(Axis axis);
};

