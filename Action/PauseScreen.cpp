#include "PauseScreen.h"
#include "InputSystem.h"
#include "UserInterfaceBase.h"

const float PauseScreen::UiSize = 2.0f;

PauseScreen::PauseScreen() :
	GameObject(),
	endPause(false),
	rePlay(false),
	casol(1),
	inputSelectedButton(false)
{
	printf("\n /********/\n    ポーズ画面    \n///********/ \n");
	//UIを生成
	backTitleButton = new UserInterfaceBase(Vector3(-200.0f, 0.0f, 0.0f), "Assets/Image/UI/TitleUi.png", Vector3(UiSize, UiSize, UiSize), 100);
	playButton = new UserInterfaceBase(Vector3(200.0f, 0.0f, 0.0f), "Assets/Image/UI/PlayUi.png", Vector3(UiSize, UiSize, UiSize), 100);
	selectedButtonLeft = new UserInterfaceBase(Vector3(-200.0f, 0.0f, 0.0f), "Assets/Image/UI/SelectedUi.png", Vector3(UiSize, UiSize, UiSize), 150);
	selectedButtonRight = new UserInterfaceBase(Vector3(200.0f, 0.0f, 0.0f), "Assets/Image/UI/SelectedUi.png", Vector3(UiSize, UiSize, UiSize), 150);
	selectedButtonRight->SetState(State::Dead);
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::PausingUpdateGameObject()
{
	//オブジェクト全体の更新が一時的に停止する、ゲーム中のポーズ画面のとき
	if (pauzingEvent == PauzingEvent::PausingEvent)
	{
		//スティックが左右に入力が行われていたとき
		if (inputDirection != 0)
		{
			//左右の入力でカーソルの位置を変更
			if (inputDirection > 0)
			{
				casol = 2;
				selectedButtonRight->SetState(State::Active);
				selectedButtonLeft->SetState(State::Dead);
			}
			else
			{
				casol = 1;
				selectedButtonLeft->SetState(State::Active);
				selectedButtonRight->SetState(State::Dead);
			}
			printf("%d", casol);
		}
		//決定の入力が行われたとき
		if (inputSelectedButton)
		{
			//カーソルによって行うイベントを変更
			switch (casol)
			{
			case(1):
				rePlay = true;
				break;
			case(2):
				endPause = true;
				break;
			}
			//決定が行われたのでUIを非表示にする
			playButton->SetState(State::Dead);
			backTitleButton->SetState(State::Dead);
			selectedButtonLeft->SetState(State::Dead);
			selectedButtonRight->SetState(State::Dead);
		}
	}
}

/*
@fn 指定の入力が会った時にフラグを建てる
*/
void PauseScreen::GameObjectInput(const InputState& _keyState)
{
	//左右の入力
	inputDirection = _keyState.Controller.GetLAxisVec().x;
	//決定入力
	inputSelectedButton = (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X)) ||
							(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y)) ||
							(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A)) ||
							(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B));
}
