#include "ComboMeanPlayerBase.h"
#include "AttackBase.h"
#include "AttackPlayerOnce.h"


ComboMeanPlayerBase::ComboMeanPlayerBase(const AttackState& _endAttack,const bool& _range):
	attackState(AttackState::NoAttack),
	endAttackState(_endAttack),
	range(_range)
{
}

ComboMeanPlayerBase::~ComboMeanPlayerBase()
{
	if (attack != nullptr)
	{
		delete attack;
		attack = nullptr;
	}
}

void ComboMeanPlayerBase::Attack(const Vector3 & _pos, const float & _direction, float & _playerCanNotMoveTime, float & _waitTimeForNextAttack)
{
	//stateパターンを使用し入力時のコンボ状態によって攻撃を変更する
	switch (attackState)
	{
	case(AttackState::NoAttack):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = GetComboAttack(attackState);
		attackState = AttackState::AttackOnce;
		break;
	case (AttackState::AttackOnce):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = GetComboAttack(attackState);
		attackState = AttackState::AttackTwice;
		break;
	case(AttackState::AttackTwice):
		if (attack != nullptr)
		{
			delete attack;
		}
		attack = GetComboAttack(attackState);
		attackState = AttackState::AttackThird;
		break;
	case(AttackState::AttackThird):
		attackState = AttackState::AttackFourth;
		break;
	case(AttackState::AttackFourth):
		break;
	case(AttackState::EndAttack):
		break;
	}

	if (attackState != AttackState::EndAttack)
	{
		if (attack != nullptr)
		{
			attack->Attack(_pos, _direction);
			_playerCanNotMoveTime = attack->GetCanNotActionTime();
			_waitTimeForNextAttack = attack->GetWaitTimeForNextAttack();
		}
	}
	if (attackState == endAttackState)
	{
		attackState = AttackState::EndAttack;
	}
}

AttackBase * ComboMeanPlayerBase::GetComboAttack(const AttackState & _attackState)
{
	return new AttackPlayerOnce();
}
