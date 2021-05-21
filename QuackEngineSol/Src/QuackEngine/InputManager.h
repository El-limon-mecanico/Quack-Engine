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

	struct KeyState {
		bool down_;
		bool pressed_;
		bool up_;
	};


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

	KeyState keys_[SDL_NUM_SCANCODES];

	std::vector<int> keysUps;
	std::vector<int> keysDown;

	bool captureMouse_ = false;

	void injectInputCegui(SDL_Event event);

	CEGUI::MouseButton sdlMouseButtonToCegui(Uint8 buttonSDL);

	Uint32 sdlKeyToCegui(SDL_Scancode sdlKeycode);

	void manageKeys(SDL_Event event);

public:

	static bool Init();
	static InputManager* Instance();

	InputManager();
	~InputManager();

	void ManageInput(SDL_Event event);
	void flushInput();

	void MouseWheelChange(int coordinate, int value);

	MousePositionAbsolute getMousePositionAbsolute();

	MousePositionRelative getMousePositionRelative();

	MouseButtons getMouseButtons();

	MouseWheel getMouseWheel();

	int getAxis(Axis axis);

	float getMouseAxis(Axis axis);

	void captureMouse();

	void releaseMouse();

	bool getKey(SDL_Scancode code);

	bool getKeyDown(SDL_Scancode code);

	bool getKeyUp(SDL_Scancode code);

	void setMouseVisibility(bool set);
};

