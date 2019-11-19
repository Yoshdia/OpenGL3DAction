#pragma once
#include "AttackBase.h"
class RangeAttackPlayer :
	public AttackBase
{
public:
	RangeAttackPlayer();
	~RangeAttackPlayer();
	void Attack(const Vector3& _ownerPosition)override;
};

