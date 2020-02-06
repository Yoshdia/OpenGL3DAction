#pragma once
#include "WeaponBase.h"
class ShotSwordWeapon :
	public WeaponBase
{
public:
	ShotSwordWeapon(const Vector3& _pos, const float& _direction, const int& _lifeCount, const int& _waitTime = 0);
	~ShotSwordWeapon();

private:
	void UpdateWeaponGameObject(float _deltaTime)override;

};

