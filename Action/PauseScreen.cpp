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
	printf("\n /********/\n    �|�[�Y���    \n///********/ \n");
	//UI�𐶐�
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
	//�I�u�W�F�N�g�S�̂̍X�V���ꎞ�I�ɒ�~����A�Q�[�����̃|�[�Y��ʂ̂Ƃ�
	if (pauzingEvent == PauzingEvent::PausingEvent)
	{
		//�X�e�B�b�N�����E�ɓ��͂��s���Ă����Ƃ�
		if (inputDirection != 0)
		{
			//���E�̓��͂ŃJ�[�\���̈ʒu��ύX
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
		//����̓��͂��s��ꂽ�Ƃ�
		if (inputSelectedButton)
		{
			//�J�[�\���ɂ���čs���C�x���g��ύX
			switch (casol)
			{
			case(1):
				rePlay = true;
				break;
			case(2):
				endPause = true;
				break;
			}
			//���肪�s��ꂽ�̂�UI���\���ɂ���
			playButton->SetState(State::Dead);
			backTitleButton->SetState(State::Dead);
			selectedButtonLeft->SetState(State::Dead);
			selectedButtonRight->SetState(State::Dead);
		}
	}
}

/*
@fn �w��̓��͂���������Ƀt���O�����Ă�
*/
void PauseScreen::GameObjectInput(const InputState& _keyState)
{
	//���E�̓���
	inputDirection = _keyState.Controller.GetLAxisVec().x;
	//�������
	inputSelectedButton = (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X)) ||
							(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y)) ||
							(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A)) ||
							(_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B));
}
