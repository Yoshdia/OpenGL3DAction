#include "InputMovePlayerComponent.h"


InputMovePlayerComponent::InputMovePlayerComponent(GameObject * owner, int updateOrder):
	Component(owner, updateOrder)
{
}

Vector3 InputMovePlayerComponent::InputMoveMent(const InputState & _state)
{
	Vector3 input = Vector3(0, 0, 0);
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
	{
		input.x++;
	}
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		input.x--;
	}
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_UP))
	{
		input.y++;
	}
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_DOWN))
	{
		input.y--;
	}
	return input;
}


