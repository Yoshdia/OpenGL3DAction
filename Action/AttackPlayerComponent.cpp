#include "AttackPlayerComponent.h"
#include "AttackPlayerOnce.h"
#include "AttackPlayerTwice.h"
#include "AttackPlayerThird.h"
#include "RangeAttackPlayer.h"
#include "GameObject.h"

AttackPlayerComponent::AttackPlayerComponent(GameObject* _owner, int _updateOrder) :
	Component(_owner, updateOrder),
	attackState(PlayerAttackState::NoAttack),
	rangeAttackState(PlayerRangeAttackState::NoRangeAttack)
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
	if (waitTimeForNextAttack < 0)
	{
		attackState = PlayerAttackState::NoAttack;
		rangeAttackState = PlayerRangeAttackState::NoRangeAttack;
	}
	else
	{
		waitTimeForNextAttack--;
	}
}

float AttackPlayerComponent::Attack()
{
	float playerCanNotMoveTime = 0.0f;

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
		if (attack != nullptr)
		{
			attack->Attack(owner->GetPosition());
			playerCanNotMoveTime = attack->GetCanNotActionTime();
			waitTimeForNextAttack = attack->GetWaitTimeForNextAttack();
		}
		else
		{
			printf("AttackPlayerComponent[Error! attack don't has instance!!]");
		}
	}
	return playerCanNotMoveTime;
}

float AttackPlayerComponent::RangeAttack()
{
	float playerCanNotMoveTime = 0.0f;

	switch (rangeAttackState)
	{
	case(PlayerRangeAttackState::NoRangeAttack):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new RangeAttackPlayer();
		rangeAttackState = PlayerRangeAttackState::RangeAttackOnce;
		break;
	case(PlayerRangeAttackState::RangeAttackOnce):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new RangeAttackPlayer();
		rangeAttackState = PlayerRangeAttackState::RangeAttackTwice;
		break;
	case(PlayerRangeAttackState::RangeAttackTwice):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new RangeAttackPlayer();
		rangeAttackState = PlayerRangeAttackState::RangeAttackThird;
		break;
	case(PlayerRangeAttackState::RangeAttackThird):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new RangeAttackPlayer();
		rangeAttackState = PlayerRangeAttackState::RangeAttackFourth;
		break;
	case(PlayerRangeAttackState::RangeAttackFourth):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = new RangeAttackPlayer();
		rangeAttackState = PlayerRangeAttackState::RangeAttackFifth;
		break;
	case(PlayerRangeAttackState::RangeAttackFifth):
		rangeAttackState = PlayerRangeAttackState::EndRangeAttack;
		break;
	}

	if (attackState != PlayerRangeAttackState::EndRangeAttack)
	{
		if (attack != nullptr)
		{
			attack->Attack(owner->GetPosition());
			playerCanNotMoveTime = attack->GetCanNotActionTime();
			waitTimeForNextAttack = attack->GetWaitTimeForNextAttack();
		}
		else
		{
			printf("AttackPlayerComponent[Error! attack don't has instance!!]");
		}
	}

	return playerCanNotMoveTime;
}
