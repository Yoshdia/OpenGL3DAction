#include "PauseScreen.h"
#include "InputSystem.h"

PauseScreen::PauseScreen():
	GameObject(),
	endPause(false)
{
	printf("\n /********/\n    �|�[�Y���    \n///********/ \n");
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::PausingUpdateGameObject()
{
}

/*
@fn �w��̓��͂���������Ƀt���O�����Ă�
*/
void PauseScreen::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_F2))
	{
		endPause = true;
	}
}
