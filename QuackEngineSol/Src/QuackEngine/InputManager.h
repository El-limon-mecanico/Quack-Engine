#pragma once

#include <memory>
#include <assert.h>
#include <SDL_scancode.h>
#include "SDL_mouse.h"
#include <CEGUI/CEGUI.h>

union SDL_Event;

class InputManager
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

	void injectInputCegui(SDL_Event event);

	CEGUI::MouseButton sdlMouseButtonToCegui(Uint8 buttonSDL);

	CEGUI::Key::Scan sdlKeyToCegui(SDL_Scancode sdlKeycode);

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

