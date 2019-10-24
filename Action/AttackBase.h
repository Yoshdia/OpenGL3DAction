#pragma once
#include "Math.h"
class AttackBase abstract
{
public:
	AttackBase();
	~AttackBase();

	virtual void Attack(const Vector3& _ownerPosition){};
	float GetCanNotActionTime() { return canNotActionTime; }
	float GetWaitTimeForNextAttack() { return waitTimeForNextAttack; }
protected:
	float canNotActionTime;
	float waitTimeForNextAttack;
};

