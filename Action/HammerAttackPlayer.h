#pragma once
#include "AttackBase.h"

class HammerAttackPlayer :
	public AttackBase
{
public:
	HammerAttackPlayer(const int& _number);
	~HammerAttackPlayer();
	void Attack(const Vector3& _ownerPosition, const int& _directiron)override;
private:
	int number;
};
