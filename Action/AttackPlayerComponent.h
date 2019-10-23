#pragma once
#include "Component.h"

enum PlayerAttackState
{
	NoAttack,
	AttackOnce,
	AttackTwice,
	EndAttack,
};

class AttackPlayerComponent :
	public Component
{
public:
	AttackPlayerComponent(GameObject* _owner, int _updateOrder );
	~AttackPlayerComponent();

	void Update(float _deltaTime);
	float Attack();
private:
	PlayerAttackState attackState;
	class AttackBase* attack;
	float waitTimeForNextAttack;
};

