#include "DoubleHammerCombo.h"
#include "HammerAttackPlayer.h"


DoubleHammerCombo::DoubleHammerCombo():
	ComboMeanPlayerBase(AttackState::AttackTwice)
{
}


DoubleHammerCombo::~DoubleHammerCombo()
{
}

AttackBase * DoubleHammerCombo::GetComboAttack(const AttackState & _attackState)
{
	switch (_attackState)
	{
	case(AttackState::NoAttack):
		return new HammerAttackPlayer(1);
		break;
	case(AttackState::AttackOnce):
		return new HammerAttackPlayer(2);
		break;
	default:
		return new HammerAttackPlayer(1);
		break;
	}
}
