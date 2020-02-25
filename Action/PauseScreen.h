#pragma once
#include "GameObject.h"

/*
@file PauseScreen.h
@brief �|�[�Y���
@sa PlaySceneObject
*/
class PauseScreen :
	public GameObject
{
public:
	PauseScreen();
	~PauseScreen();

	void PausingUpdateGameObject()override;
	/*
	@fn �w��̓��͂���������Ƀt���O�����Ă�
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:
	//�|�[�Y��ʂ̏I��
	bool endPause;
	//�|�[�Y��ʂŃ��v���C��I�����ꂽ
	bool rePlay;
	//�Q�[�����ĊJ����UI
	class UserInterfaceBase* playButton;
	//�^�C�g���֖߂�UI
	class UserInterfaceBase* backTitleButton;
	//����(�^�C�g���֖߂�)�ɕ\������AUI�̈ʒu��\�����邽�߂̔������̍�����
	class UserInterfaceBase* selectedButtonLeft;
	//�E��(�Q�[�����ĊJ����)casol�ɂ���đI������Ă���UI�̈ʒu��\�����邽�߂̔������̍�����
	class UserInterfaceBase* selectedButtonRight;
	//playButton�AbackTitleButton�̃T�C�Y
	static const float UiSize;
	//�I�𒆂̃J�[�\���ʒu
	int casol;
	//�I�����̌������
	bool inputSelectedButton;
	//�I�𒆂̃J�[�\���ʒu
	int inputDirection;
public: //�Q�b�^�[�Z�b�^�[
	/*
@return �|�[�Y��ʂ̏I���t���O
*/
	bool GetEndPause() { return endPause; }

	/*
@return �|�[�Y��ʂ̂�蒼���t���O
*/
	bool GetRePlayFlag() { return rePlay; }
};

