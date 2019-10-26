#pragma once
#include "AttackBase.h"
class AttackPlayerThird :
	public AttackBase
{
public:
	AttackPlayerThird();
	~AttackPlayerThird();

	void Attack(const Vector3& _ownerPosition)override;
};

