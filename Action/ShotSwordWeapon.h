#pragma once
#include "WeaponBase.h"

/*
@file ShotSwordWeapon.h
@brief ���Ő؂镐��
*/
class ShotSwordWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos ���W
	@param _directipn ����
	@param _lifeCount ��������
	@param _waitTime �ҋ@����
	*/
	ShotSwordWeapon(const Vector3& _pos, const float& _direction, const int& _lifeCount, const int& _waitTime = 0);
	~ShotSwordWeapon();

private:
	/*
@fn �������Ԃ����ȏ�ɂȂ�Ɖ�]���x��ύX����
*/
	void UpdateWeaponGameObject(float _deltaTime)override;

};

