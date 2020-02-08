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
	bool endPause;
public: //�Q�b�^�[�Z�b�^�[
	/*
@return �|�[�Y��ʂ̏I���t���O
*/
	bool GetEndPause() { return endPause; }
};

