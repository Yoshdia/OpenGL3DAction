#include "AttackPlayerComponent.h"
#include "AttackPlayerOnce.h"
#include "AttackPlayerTwice.h"
#include "AttackPlayerThird.h"
#include "RangeAttackPlayer.h"
#include "GameObject.h"
#include "ComboMeanPlayerBase.h"
#include "RotateTripleWeaponCombo.h"
#include "ThrowWeaponCombo.h"

AttackPlayerComponent::AttackPlayerComponent(GameObject* _owner, int _updateOrder) :
	Component(_owner, updateOrder),
	waitTimeForNextAttack(0)
{
	firstSlotAttack = new RotateTripleWeaponCombo();
	secondSlotAttack = new ThrowWeaponCombo();
}

AttackPlayerComponent::~AttackPlayerComponent()
{
	if (firstSlotAttack != nullptr)
	{
		delete firstSlotAttack;
	}
	if (secondSlotAttack != nullptr)
	{
		delete secondSlotAttack;
	}
}

void AttackPlayerComponent::Update(float _deltaTime)
{
	if (waitTimeForNextAttack < 0)
	{
		//コンボ状態をリセットする
		firstSlotAttack->ComboReset();
		secondSlotAttack->ComboReset();
	}
	else
	{
		waitTimeForNextAttack--;
	}
}

float AttackPlayerComponent::Attack(int _direction)
{
	float playerCanNotMoveTime = 0.0f;

	if (firstSlotAttack != nullptr)
	{
		firstSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
	}

	return playerCanNotMoveTime;
}

float AttackPlayerComponent::RangeAttack(int _direction)
{
	float playerCanNotMoveTime = 0.0f;

	if (secondSlotAttack != nullptr)
	{
		secondSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
	}

	return playerCanNotMoveTime;
}
