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
@fn AttackPlayerComponent����Ă΂��B�U�����s��
@param _pos �U�����s�����W
@param _direction �U�����s������
@param &_playerCanNotMoveTime �U����v���C���[�̍s���s���ԁA�d������������ϐ��ւ̎Q��
@param &_waitTimeForNextAttack �U����d�����玟�̍U���܂ł̎��Ԃ���������ϐ��ւ̎Q��
*/
void ComboMeanPlayerBase::Attack(const Vector3 & _pos, const float & _direction, float & _playerCanNotMoveTime, float & _waitTimeForNextAttack)
{
	//state�p�^�[�����g�p�����͎��̃R���{��Ԃɂ���čU����ύX����
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
@fn �p����N���X�Ŏw��A���ʎq_attackState�����ƂɍU������
@param _attackState ���݂̃R���{��n��
@return �U���N���X
*/
AttackBase * ComboMeanPlayerBase::GetComboAttack(const AttackState & _attackState)
{
	return new AttackPlayerOnce();
}
