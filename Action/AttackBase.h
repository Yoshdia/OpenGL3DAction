#pragma once

class AttackBase abstract
{
public:
	AttackBase();
	~AttackBase();

	virtual void Attack() {};
	float GetCanNotActionTime() { return canNotActionTime; }
	float GetWaitTimeForNextAttack() { return waitTimeForNextAttack; }
protected:
	float canNotActionTime;
	float waitTimeForNextAttack;
};

