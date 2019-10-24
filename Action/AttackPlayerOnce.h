#pragma once
#include "AttackBase.h"

class AttackPlayerOnce :
	public AttackBase
{
public:
	AttackPlayerOnce();
	~AttackPlayerOnce();
	void Attack(const Vector3& _ownerPosition)override;
};

