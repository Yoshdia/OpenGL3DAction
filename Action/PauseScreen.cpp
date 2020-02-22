#include "PauseScreen.h"
#include "InputSystem.h"
#include "UserInterfaceBase.h"

PauseScreen::PauseScreen() :
	GameObject(),
	endPause(false),
	rePlay(false)
{
	printf("\n /********/\n    ポーズ画面    \n///********/ \n");

	replayButton = new UserInterfaceBase(Vector3(100, 0, 0), "Assets/Image/", Vector3(10, 10, 10));
	returnButton = new UserInterfaceBase(Vector3(-100, 0, 0), "", Vector3(10, 10, 10));
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
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_F3)||
		(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X))&&
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_START))
	{
		rePlay = true;
	}

}
