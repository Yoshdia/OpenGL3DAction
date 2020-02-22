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

	GameObject* replayButton;
	GameObject* returnButton;


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

