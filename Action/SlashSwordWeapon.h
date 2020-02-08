#pragma once
#include "WeaponBase.h"
class SlashSwordWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos ���W
	@param _stage �i�K
	@param _direction ����
	@param _lifeCount ��������
	@param _waitTime �ҋ@���� 
	*/
	SlashSwordWeapon(const Vector3& _pos, const int& _stage, const float& _direction, const int& _lifeCount, const int& _waitTime = 0);
	~SlashSwordWeapon();
private:
	/*
@fn �������Ԃ����ȏ�ɂȂ�Ɖ�]���x��ύX����
*/
	void UpdateWeaponGameObject(float _deltaTime)override;
	//��]���x
	int rotateSpeed;
	//��]����
	int rotateDirection;
	//�ړ��\��n�_
	Vector3 targetPos;
};

