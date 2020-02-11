#pragma once
#include "UserInterfaceBase.h"
/*
@file TakeItemUi.h
@brief �A�C�e���擾�����ۂɁA��ʒ����ɃA�C�R�����o�����A�C�e���̈ʒu�֔��ł������o
*/
class TakeItemUi :
	public UserInterfaceBase
{
public:
	/*
	@param _pos �J�n���W
	@param _targetSlot �ړI�n
	@param _spriteName �摜�A�h���X
	@param _size �摜�T�C�Y
	*/
	TakeItemUi(const Vector3& _pos, const Vector3& targetSlot, const std::string& _spriteName, const Vector3& _size);
	~TakeItemUi();

	/*
	@fn ���W����ڕW�܂ňړ����A�������Ԃ��J�E���g�_�E������
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	//�ړI�n
	Vector3 target;
	//��������
	int life;
};

