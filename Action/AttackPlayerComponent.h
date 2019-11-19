#pragma once
#include "Component.h"

/*
	 @enum PlayerAttackState
	 Player�̋ߐڃR���{�̏��
*/
enum PlayerAttackState
{
	NoAttack,
	AttackOnce,
	AttackTwice,
	AttackThird,
	EndAttack,
};

/*
 @file AttackPlayerComponent.h
 @brief Player�ɋߐڃR���{�A�������U�����s�킹��N���X
	*/
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
	unsigned int rangeAttackCount;
	class AttackBase* attack;
	float waitTimeForNextAttack;
};

