#pragma once

#include "GameObject.h"

class Ship : public GameObject
{
public:
	/**
	@param	�Q�[���N���X�̃|�C���^
	*/
	Ship();
	~Ship();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
};

