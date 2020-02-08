#pragma once
#include "UserInterfaceBase.h"

/*
@file HaveLifeCountUI.h
@fn ��Ƀv���C���[�̗̑͂����������Ƃ��̉��o�ŗp������A�������Ԃ�������UI
*/
class HaveLifeCountUI :
	public UserInterfaceBase
{
public:
	/*
	@param _pos �X�N���[�����W
	@param _spriteName �摜�ւ̃A�h���X
	@param _lifeCount ��������
	@param _size �T�C�Y
	@param _drawOrder �`�揇
	*/
	HaveLifeCountUI(const Vector3& _pos, const std::string& _spriteName, int _lifeCount, const Vector3& _size = Vector3(1, 1, 1), const int& _drawOrder = 100);
	~HaveLifeCountUI();

	/*
	@fn �������Ԃ��J�E���g����
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	int lifeCount;
};


