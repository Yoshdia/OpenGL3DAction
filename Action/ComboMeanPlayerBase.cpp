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

/*
@fn AttackPlayerComponentから呼ばれる。攻撃を行う
@param _pos 攻撃を行う座標
@param _direction 攻撃を行う向き
@param &_playerCanNotMoveTime 攻撃後プレイヤーの行動不可時間、硬直を所持する変数への参照
@param &_waitTimeForNextAttack 攻撃後硬直から次の攻撃までの時間を所持する変数への参照
*/
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

/*
@fn 継承先クラスで指定、識別子_attackStateをもとに攻撃する
@param _attackState 現在のコンボを渡す
@return 攻撃クラス
*/
AttackBase * ComboMeanPlayerBase::GetComboAttack(const AttackState & _attackState)
{
	return new AttackPlayerOnce();
}
