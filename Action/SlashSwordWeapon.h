#pragma once
#include "WeaponBase.h"
class SlashSwordWeapon :
	public WeaponBase
{
public:
	SlashSwordWeapon(const Vector3& _pos, const int& _stage, const float& _direction, const int& _lifeCount, const int& _waitTime = 0);
	~SlashSwordWeapon();
private:
	void UpdateWeaponGameObject(float _deltaTime)override;
	int rotateSpeed;
	int rotateDirection;
	Vector3 targetPos;
};

