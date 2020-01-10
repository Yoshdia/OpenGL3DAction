#pragma once
#include "WeaponBase.h"

class HammerWeapon :
	public WeaponBase
{
public:
	HammerWeapon(const Vector3& _pos,const int& number, const int& _direction,const int& _lifeCount, const int& _waitTime = 0);
	~HammerWeapon();
private:
	void UpdateWeaponGameObject(float _deltaTime)override;
	int rotateSpeed;
};

