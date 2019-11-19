#pragma once
#include "Component.h"

enum PlayerAttackState
{
	NoAttack,
	AttackOnce,
	AttackTwice,
	AttackThird,
	EndAttack,
};

enum PlayerRangeAttackState
{
	NoRangeAttack,
	RangeAttackOnce,
	RangeAttackTwice,
	RangeAttackThird,
	RangeAttackFourth,
	RangeAttackFifth,
	EndRangeAttack,
};

class AttackPlayerComponent :
	public Component
{
public:
	AttackPlayerComponent(GameObject* _owner, int _updateOrder );
	~AttackPlayerComponent();

	void Update(float _deltaTime);
	float Attack();
	float RangeAttack();
private:
	PlayerAttackState attackState;
	PlayerRangeAttackState rangeAttackState;
	class AttackBase* attack;
	float waitTimeForNextAttack;
};

