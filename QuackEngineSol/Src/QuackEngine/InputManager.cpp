#include "InputManager.h"

#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include <iostream>

std::unique_ptr<InputManager> InputManager::instance_;

void InputManager::inputToCegui(SDL_Event event)
{
	//TODO EL INYECTAR EL INPUT EN CEGUI 
}


bool InputManager::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new InputManager());
	return instance_.get();
}

InputManager* InputManager::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

InputManager::~InputManager()
{
}

void InputManager::ManageInput(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		mousePosition = { event.motion.x , event.motion.y };
		std::cout << "INPUT MANAGER POS RATON: " << event.motion.x << " , "<< event.motion.y << "\n";
		break;
	case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			mouseButtons.leftDown = event.button.state;
			std::cout << "INPUT MANAGER BOTON IZQUIERDO RATON PULSADO: " << event.button.state << "\n";
			break;
		case SDL_BUTTON_MIDDLE:
			mouseButtons.middleDown = event.button.state;
			std::cout << "INPUT MANAGER BOTON RULETA RATON PULSADO: " << event.button.state << "\n";
			break;
		case SDL_BUTTON_RIGHT:
			mouseButtons.rightDown = event.button.state;
			std::cout << "INPUT MANAGER BOTON DERECHO RATON PULSADO: " << event.button.state << "\n";
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEWHEEL:
		if (mouseWheel.x != event.wheel.x)
		{
			MouseWheelChange(0, event.wheel.x);
			std::cout << "INPUT MANAGER RUEDA X: " << event.wheel.x << "\n";
		}else if (mouseWheel.y != event.wheel.y)
		{
			MouseWheelChange(1, event.wheel.y);
			std::cout << "INPUT MANAGER RUEDA Y: " << event.wheel.y << "\n";
		}
	default:
		break;
	}

	inputToCegui(event);
}

bool InputManager::isKeyDown(SDL_Scancode code)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	return state[code];
}

void InputManager::MouseWheelChange(int coordinate, int value)
{
	if (coordinate) {
		mouseWheel.y = value;
	}
	else mouseWheel.x = value;
}

InputManager::MousePosition InputManager::getMousePosition()
{
	return mousePosition;
}

InputManager::MouseButtons InputManager::getMouseButtons()
{
	return mouseButtons;
}

InputManager::MouseWheel InputManager::getMouseWheel()
{
	return mouseWheel;
}
