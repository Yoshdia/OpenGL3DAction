#include "ThrowWeaponCombo.h"
#include "RangeAttackPlayer.h"

ThrowWeaponCombo::ThrowWeaponCombo():
	ComboMeanPlayerBase(AttackState::AttackThird,true)
{
}

ThrowWeaponCombo::~ThrowWeaponCombo()
{
}

AttackBase * ThrowWeaponCombo::GetComboAttack(const AttackState & _attackState)
{
	switch (_attackState)
	{
	case(AttackState::NoAttack):
		return new RangeAttackPlayer();
		break;
	case(AttackState::AttackOnce):
		return new RangeAttackPlayer();
		break;
	case(AttackState::AttackTwice):
		return new RangeAttackPlayer();
		break;
	default:
		return new RangeAttackPlayer();
		break;
	}
}
