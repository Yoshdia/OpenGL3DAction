#pragma once
#include "GameObject.h"
class WallObject :
	public GameObject
{
public:
	WallObject(int _i);
	~WallObject();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	GameObject* player;
};

