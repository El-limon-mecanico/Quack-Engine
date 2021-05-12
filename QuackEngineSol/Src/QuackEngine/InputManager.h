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

union SDL_Event;

class QUACK_ENGINE_PRO_API InputManager
{
private:
	static std::unique_ptr<InputManager> instance_;

	struct MousePosition
	{
		int x = 0;
		int y = 0;
	} mousePosition;

	struct MouseButtons {
		bool leftDown = false;
		bool middleDown = false;
		bool rightDown = false;
	}mouseButtons;

	struct MouseWheel {
		int x = 0;
		int y = 0;
	}mouseWheel;

	void inputToCegui(SDL_Event event);

public:

	static bool Init();
	static InputManager* Instance();

	InputManager() {}
	~InputManager();

	void ManageInput(SDL_Event event);

	void MouseWheelChange(int coordinate, int value);

	MousePosition getMousePosition();

	MouseButtons getMouseButtons();

	MouseWheel getMouseWheel();

	bool isKeyDown(SDL_Scancode code);
};

