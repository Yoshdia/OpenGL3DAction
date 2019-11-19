#pragma once
#include "Math.h"

/*
 @file AttackBase.h
 @brief �v���C���[�̍U�����N���X�BAttack���̊֐��ōU�����e�����肷��
	*/
class AttackBase abstract
{
public:
	AttackBase();
	~AttackBase();
	/*
  @fn �U�����e
@param _ownerPosition �U���������W
*/
	virtual void Attack(const Vector3& _ownerPosition) {};
	/*
	  @fn �Q�b�^�[
	*/
	float GetCanNotActionTime() { return canNotActionTime; }
	float GetWaitTimeForNextAttack() { return waitTimeForNextAttack; }
protected:
	//�h���N���X�Ō��肷��l�B�h���N���X�̍U�����s�����ۂɃv���C���[�ɔ�������ړ��s����(�d��)
	float canNotActionTime;
	//�h���N���X�Ō��肷��l�B���̍U���ɔh��������P�\����(�R���{�P�\����)
	float waitTimeForNextAttack;
};

