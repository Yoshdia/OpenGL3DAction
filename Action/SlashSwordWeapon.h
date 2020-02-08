#pragma once
#include "WeaponBase.h"
class SlashSwordWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos 座標
	@param _stage 段階
	@param _direction 向き
	@param _lifeCount 生存時間
	@param _waitTime 待機時間 
	*/
	SlashSwordWeapon(const Vector3& _pos, const float& _stage, const float& _direction, const int& _lifeCount, const int& _waitTime = 0);
	~SlashSwordWeapon();
private:
	/*
@fn 活動時間が一定以上になると回転速度を変更する
*/
	void UpdateWeaponGameObject(float _deltaTime)override;
	//回転速度
	float rotateSpeed;
	//回転向き
	float rotateDirection;
	//移動予定地点
	Vector3 targetPos;
};

