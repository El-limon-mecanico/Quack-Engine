
#include <CEGUI/CEGUI.h>
#include "InputManager.h"

#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <iostream>
#include "CEGUIQuack.h"
#include "OgreQuack.h"

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
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(mousePositionAbsolute_.x, mousePositionAbsolute_.y);
	}
	else if (event.type == SDL_KEYDOWN)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)sdlKeyToCegui(event.key.keysym.scancode));
	}
	else if (event.type == SDL_KEYUP)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)sdlKeyToCegui(event.key.keysym.scancode));
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

Uint32 InputManager::sdlKeyToCegui(SDL_Scancode sdlKeycode)
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

InputManager::InputManager() :
	keysUps(std::vector<int>())
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		keys_[i] = { false,false,false };
	}
}

InputManager::~InputManager()
{
}

void InputManager::ManageInput(SDL_Event event)
{

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		mousePositionAbsolute_ = { event.motion.x , event.motion.y };
		//std::cout << "INPUT MANAGER POS RATON: " << event.motion.x << " , " << event.motion.y << "\n";
		if (captureMouse_) SDL_WarpMouseInWindow(NULL, OgreQuack::Instance()->getWindowW() / 2, OgreQuack::Instance()->getWindowH() / 2);
		break;
	case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			mouseButtons_.leftDown = event.button.state;
			//std::cout << "INPUT MANAGER BOTON IZQUIERDO RATON PULSADO: " << event.button.state << "\n";
			break;
		case SDL_BUTTON_MIDDLE:
			mouseButtons_.middleDown = event.button.state;
			//std::cout << "INPUT MANAGER BOTON RULETA RATON PULSADO: " << event.button.state << "\n";
			break;
		case SDL_BUTTON_RIGHT:
			mouseButtons_.rightDown = event.button.state;
			//std::cout << "INPUT MANAGER BOTON DERECHO RATON PULSADO: " << event.button.state << "\n";
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEWHEEL:
		if (mouseWheel_.x != event.wheel.x)
		{
			MouseWheelChange(0, event.wheel.x);
			//std::cout << "INPUT MANAGER RUEDA X: " << event.wheel.x << "\n";
		}
		else if (mouseWheel_.y != event.wheel.y)
		{
			MouseWheelChange(1, event.wheel.y);
			//std::cout << "INPUT MANAGER RUEDA Y: " << event.wheel.y << "\n";
		}
		break;
	default:
		manageKeys(event);
		break;
	}


	injectInputCegui(event);
}

void InputManager::manageKeys(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode code = event.key.keysym.scancode;
		if (!keys_[code].pressed_) {
			keys_[code].down_ = true;
			keys_[code].pressed_ = true;
			keysDown.push_back(code);
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		SDL_Scancode code = event.key.keysym.scancode;
		keys_[code].pressed_ = false;
		keys_[code].down_ = false;
		keys_[code].up_ = true;
		keysUps.push_back(code);
	}
}

void InputManager::flushKeys()
{
	for (int c : keysUps)
		keys_[c].up_ = false;
	keysUps.clear();
	for (int c : keysDown)
		keys_[c].down_ = false;
	keysDown.clear();
}

int InputManager::getAxis(Axis axis)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (axis == Vertical)  return (1 * (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])) + (-1 * (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]));
	if (axis == Horizontal)  return (1 * (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])) + (-1 * (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]));

}

void InputManager::captureMouse()
{
	captureMouse_ = true;
}

void InputManager::releaseMouse()
{
	captureMouse_ = false;
}

bool InputManager::getKey(SDL_Scancode code)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	return state[code];
}

bool InputManager::getKeyDown(SDL_Scancode code)
{
	return keys_[code].down_;
}

bool InputManager::getKeyUp(SDL_Scancode code)
{
	return keys_[code].up_;
}

void InputManager::MouseWheelChange(int coordinate, int value)
{
	if (coordinate) {
		mouseWheel_.y = value;
	}
	else mouseWheel_.x = value;
}

//devuelve un struct con (dos int) x,y coordenadas del raton, con origen en la esquina superior izquierda
InputManager::MousePositionAbsolute InputManager::getMousePositionAbsolute()
{
	return mousePositionAbsolute_;
}

//devuelve un struct con (dos double) x,y coordenadas del raton en valor relativo(de 0,0 a 1,1), con origen en la esquina superior izquierda
InputManager::MousePositionRelative InputManager::getMousePositionRelative()
{
	mousePositionRelative_ = { (float)mousePositionAbsolute_.x / OgreQuack::Instance()->getWindowW(),
								(float)mousePositionAbsolute_.y / OgreQuack::Instance()->getWindowH() };
	return mousePositionRelative_;
}

//devuelve un struct con booleanos que estan en true cuando se pulsa y pasan a false al soltar
InputManager::MouseButtons InputManager::getMouseButtons()
{
	return mouseButtons_;
}

//devuelve un struct con coordenadas x e y y el cambio en el ultimo bucle (si scrolleas hacia abajo, la componente y sería -1)
InputManager::MouseWheel InputManager::getMouseWheel()
{
	return mouseWheel_;
}
