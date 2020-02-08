#include "PauseScreen.h"
#include "InputSystem.h"

PauseScreen::PauseScreen():
	GameObject(),
	endPause(false)
{
	printf("\n /********/\n    ポーズ画面    \n///********/ \n");
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::PausingUpdateGameObject()
{
}

/*
@fn 指定の入力が会った時にフラグを建てる
*/
void PauseScreen::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_F2))
	{
		endPause = true;
	}
}
