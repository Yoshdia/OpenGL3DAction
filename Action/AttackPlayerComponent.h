#pragma once
#include "Component.h"

/*
	 @enum PlayerAttackState
	 Playerの近接コンボの状態
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
 @brief Playerに近接コンボ、遠距離攻撃を行わせるクラス
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

