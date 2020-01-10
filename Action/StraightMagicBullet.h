#pragma once
#include "WeaponBase.h"
class StraightMagicBullet :
	public WeaponBase
{
public:
	StraightMagicBullet(const Vector3& _shotPosition, const Vector3& _targetPosition, const int& _waitCount);
	~StraightMagicBullet();

private:
	void UpdateWeaponGameObject(float _deltaTime)override;
	Vector3 force;
};

