#pragma once
#include "WeaponBase.h"

/*
@file HammerWeapon.h
@brief 降り下ろすような回転を行うハンマー武器
*/
class HammerWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos 座標
	@param _number コンボ回数
	@param _direction 向き
	@param _lifeCount 生存時間
	@param _waitTime　待機時間
	*/
	HammerWeapon(const Vector3& _pos,const float& number, const float& _direction,const int& _lifeCount, const int& _waitTime = 0);
	~HammerWeapon();
private:
	/*
	@fn 活動時間が一定以上になると回転速度を変更する
	*/
	void UpdateWeaponGameObject(float _deltaTime)override;
	float rotateSpeed;
};

