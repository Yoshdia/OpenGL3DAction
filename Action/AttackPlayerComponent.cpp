#include "AttackPlayerComponent.h"
#include "AttackPlayerOnce.h"
#include "AttackPlayerTwice.h"
#include "AttackPlayerThird.h"
#include "GameObject.h"

AttackPlayerComponent::AttackPlayerComponent(GameObject* _owner, int _updateOrder) :
	Component(_owner, updateOrder),
	attackState(PlayerAttackState::NoAttack)
{
	attack = nullptr;
}


AttackPlayerComponent::~AttackPlayerComponent()
{
	if (attack != nullptr)
	{
		delete attack;
	}
}

void AttackPlayerComponent::Update(float _deltaTime)
{
}

float AttackPlayerComponent::Attack()
{
	float playerCanNotMoveTime = 0.0f;

	if (waitTimeForNextAttack < 0)
	{
		attackState = PlayerAttackState::NoAttack;
	}
	else
	{
		waitTimeForNextAttack--;
	}

	switch (attackState)
	{
	case(PlayerAttackState::NoAttack):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new AttackPlayerOnce;
		attackState = PlayerAttackState::AttackOnce;
		break;
	case (PlayerAttackState::AttackOnce):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new AttackPlayerTwice();
		attackState = PlayerAttackState::AttackTwice;
		break;
	case(PlayerAttackState::AttackTwice):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new AttackPlayerThird();
		attackState = PlayerAttackState::AttackThird;
		break;
	case(PlayerAttackState::AttackThird):
		attackState = PlayerAttackState::EndAttack;
		break;
	}

	if (attackState != PlayerAttackState::EndAttack)
	{
		attack->Attack(owner->GetPosition());
		playerCanNotMoveTime = attack->GetCanNotActionTime();
		waitTimeForNextAttack = attack->GetWaitTimeForNextAttack();
	}
	return playerCanNotMoveTime;
}
