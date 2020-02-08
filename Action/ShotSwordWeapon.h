#pragma once
#include "WeaponBase.h"

/*
@file ShotSwordWeapon.h
@brief 剣で切る武器
*/
class ShotSwordWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos 座標
	@param _directipn 向き
	@param _lifeCount 生存時間
	@param _waitTime 待機時間
	*/
	ShotSwordWeapon(const Vector3& _pos, const float& _direction, const int& _lifeCount, const int& _waitTime = 0);
	~ShotSwordWeapon();

private:
	/*
@fn 活動時間が一定以上になると回転速度を変更する
*/
	void UpdateWeaponGameObject(float _deltaTime)override;

};

