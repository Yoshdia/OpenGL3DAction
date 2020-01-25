#pragma once
#include "AttackBase.h"

class HammerAttackPlayer :
	public AttackBase
{
public:
	HammerAttackPlayer(const float& _number);
	~HammerAttackPlayer();
	void Attack(const Vector3& _ownerPosition, const float& _direction)override;
private:
	float number;
};

