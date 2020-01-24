#include "PauseScreen.h"
#include "InputSystem.h"

PauseScreen::PauseScreen():
	GameObject(),
	endPause(false)
{
	printf("\n /*********/\n    É|Å[ÉYâÊñ     \n///*********/ \n");
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::PausingUpdateGameObject()
{
}

void PauseScreen::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_F2))
	{
		endPause = true;
	}
}
