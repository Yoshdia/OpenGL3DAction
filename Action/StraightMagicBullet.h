#pragma once
#include "WeaponBase.h"
/*
@file StraightMagicBullet.h
@brief�@�ڕW�Ɍ����Ē��i���閂�@�̒e
*/
class StraightMagicBullet :
	public WeaponBase
{
public:
	/*
	@param _shotPosition ���W
	@param _targetPosition �ڕW���W
	@param _waitCount �ҋ@����
	*/
	StraightMagicBullet(const Vector3& _shotPosition, const Vector3& _targetPosition, const int& _waitCount);
	~StraightMagicBullet();

private:
	/*
@fn �͂̕����֐i�s����
*/
	void UpdateWeaponGameObject(float _deltaTime)override;
	//�͂̕���
	Vector3 force;
};

