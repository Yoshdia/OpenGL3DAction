#pragma once
#include "AttackBase.h"
class AttackPlayerTwice final :
	public AttackBase
{
public:
	AttackPlayerTwice();
	~AttackPlayerTwice();

	void Attack(const Vector3& _ownerPosition)override;
};

