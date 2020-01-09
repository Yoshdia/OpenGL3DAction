#include "RotateTripleWeaponCombo.h"

#include "AttackPlayerOnce.h"
#include "AttackPlayerTwice.h"
#include "AttackPlayerThird.h"




RotateTripleWeaponCombo::RotateTripleWeaponCombo():
	ComboMeanPlayerBase(AttackState::AttackThird)
{
}

RotateTripleWeaponCombo::~RotateTripleWeaponCombo()
{
}

AttackBase * RotateTripleWeaponCombo::GetComboAttack(const AttackState & _attackState)
{
	switch (_attackState)
	{
	case(AttackState::NoAttack):
		return new AttackPlayerOnce();
		break;
	case(AttackState::AttackOnce):
		return new AttackPlayerTwice();
		break;
	case(AttackState::AttackTwice):
		return new AttackPlayerThird();
		break;
	default:	
		return new AttackPlayerOnce();
		break;
	}
}
