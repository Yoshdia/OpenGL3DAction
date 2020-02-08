#pragma once
#include "WeaponBase.h"
/*
@file StraightMagicBullet.h
@brief　目標に向けて直進する魔法の弾
*/
class StraightMagicBullet :
	public WeaponBase
{
public:
	/*
	@param _shotPosition 座標
	@param _targetPosition 目標座標
	@param _waitCount 待機時間
	*/
	StraightMagicBullet(const Vector3& _shotPosition, const Vector3& _targetPosition, const int& _waitCount);
	~StraightMagicBullet();

private:
	/*
@fn 力の方向へ進行する
*/
	void UpdateWeaponGameObject(float _deltaTime)override;
	//力の方向
	Vector3 force;
};

