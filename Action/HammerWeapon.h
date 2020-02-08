#pragma once
#include "WeaponBase.h"

/*
@file HammerWeapon.h
@brief �~�艺�낷�悤�ȉ�]���s���n���}�[����
*/
class HammerWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos ���W
	@param _number �R���{��
	@param _direction ����
	@param _lifeCount ��������
	@param _waitTime�@�ҋ@����
	*/
	HammerWeapon(const Vector3& _pos,const float& number, const float& _direction,const int& _lifeCount, const int& _waitTime = 0);
	~HammerWeapon();
private:
	/*
	@fn �������Ԃ����ȏ�ɂȂ�Ɖ�]���x��ύX����
	*/
	void UpdateWeaponGameObject(float _deltaTime)override;
	float rotateSpeed;
};

