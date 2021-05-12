#include "InputManager.h"

#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <iostream>
#include "CEGUIQuack.h"

std::unique_ptr<InputManager> InputManager::instance_;

void InputManager::injectInputCegui(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) 
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(sdlMouseButtonToCegui(event.button.button));
	}
	else if (event.type == SDL_MOUSEBUTTONUP) 
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(sdlMouseButtonToCegui(event.button.button));
	}
	else if (event.type == SDL_MOUSEMOTION) 
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(mousePosition.x, mousePosition.y);
	}
	else if (event.type == SDL_KEYDOWN) 
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(sdlKeyToCegui(event.key.keysym.scancode));
	}
	else if (event.type == SDL_KEYUP) 
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(sdlKeyToCegui(event.key.keysym.scancode));
	}
	else if (event.type == SDL_MOUSEWHEEL) 
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(event.wheel.y);
	}
}

CEGUI::MouseButton InputManager::sdlMouseButtonToCegui(Uint8 buttonSDL)
{
	switch (buttonSDL)
	{
	case SDL_BUTTON_LEFT:
		return CEGUI::MouseButton::LeftButton;
	case SDL_BUTTON_RIGHT:
		return CEGUI::MouseButton::RightButton;
	case SDL_BUTTON_MIDDLE:
		return CEGUI::MouseButton::MiddleButton;
	default:
		return CEGUI::MouseButton::NoButton;
	}
}

CEGUI::Key::Scan InputManager::sdlKeyToCegui(SDL_Scancode sdlKeycode)
{
	switch (sdlKeycode)
	{
	case SDLK_w:
		return CEGUI::Key::W;
	case SDLK_a:
		return CEGUI::Key::A;
	case SDLK_s:
		return CEGUI::Key::S;
	case SDLK_d:
		return CEGUI::Key::D;
	case SDLK_LEFT:
		return CEGUI::Key::ArrowLeft;
	case SDLK_RIGHT:
		return CEGUI::Key::ArrowRight;
	case SDLK_UP:
		return CEGUI::Key::ArrowUp;
	case SDLK_DOWN:
		return CEGUI::Key::ArrowDown;
	case SDLK_ESCAPE:
		return CEGUI::Key::Escape;
	case SDLK_INSERT:
		return CEGUI::Key::Insert;
	case SDLK_SPACE:
		return CEGUI::Key::Space;
	default:
		return CEGUI::Key::Unknown;
	}
};

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
		//std::cout << "INPUT MANAGER POS RATON: " << event.motion.x << " , " << event.motion.y << "\n";
		break;
	case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			mouseButtons.leftDown = event.button.state;
			//std::cout << "INPUT MANAGER BOTON IZQUIERDO RATON PULSADO: " << event.button.state << "\n";
			break;
		case SDL_BUTTON_MIDDLE:
			mouseButtons.middleDown = event.button.state;
			//std::cout << "INPUT MANAGER BOTON RULETA RATON PULSADO: " << event.button.state << "\n";
			break;
		case SDL_BUTTON_RIGHT:
			mouseButtons.rightDown = event.button.state;
			//std::cout << "INPUT MANAGER BOTON DERECHO RATON PULSADO: " << event.button.state << "\n";
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEWHEEL:
		if (mouseWheel.x != event.wheel.x)
		{
			MouseWheelChange(0, event.wheel.x);
			//std::cout << "INPUT MANAGER RUEDA X: " << event.wheel.x << "\n";
		}
		else if (mouseWheel.y != event.wheel.y)
		{
			MouseWheelChange(1, event.wheel.y);
			//std::cout << "INPUT MANAGER RUEDA Y: " << event.wheel.y << "\n";
		}
		break;
	default:
		break;
	}

	injectInputCegui(event);
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
