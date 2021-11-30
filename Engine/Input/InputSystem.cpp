#include "InputSystem.h"

namespace nc
{
	InputSystem::eKeyState nc::InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsKeyDown(id);
		bool prevKeyDown = isPreviousKeyDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
		}
		return state;
	}

	bool nc::InputSystem::IsKeyDown(int id)
	{
		return keyboardState[id];
	}

	bool nc::InputSystem::isPreviousKeyDown(int id)
	{
		return prevKeyboardState[id];
	}

	void InputSystem::Startup()
	{
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
		keyboardState.resize(numKeys);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

		prevKeyboardState = keyboardState;

		// set initial mouse position
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = glm::vec2{ x , y };
		prevMousePosition = mousePosition;
	}

	void InputSystem::Shutdown()
	{

	}

	void InputSystem::Update(float dt)
	{
		prevKeyboardState = keyboardState;

		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

		prevMouseButtonState = mouseButtonState;
		prevMousePosition = mousePosition;
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = glm::vec3{ x, y, 0 };
		mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;
		mouseButtonState[1] = buttons & SDL_BUTTON_MMASK;
		mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;
		mouseRelative = mousePosition - prevMousePosition;
	}

	InputSystem::eKeyState InputSystem::GetButtonState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsButtonDown(id);
		bool prevKeyDown = IsPrevButtonDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
		}
		return state;
	}
}
