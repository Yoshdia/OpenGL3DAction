#include "TripleSlashSwordCombo.h"
#include "SlashSwordAttackPlayer.h"

TripleSlashSwordCombo::TripleSlashSwordCombo() :
	ComboMeanPlayerBase(AttackState::AttackThird)
{

}
TripleSlashSwordCombo::~TripleSlashSwordCombo()
{
}

AttackBase* TripleSlashSwordCombo::GetComboAttack(const AttackState& _attackState)
{
	switch (_attackState)
	{
	case(AttackState::NoAttack):
		return new SlashSwordAttackPlayer(1);
		break;
	case(AttackState::AttackOnce):
		return new SlashSwordAttackPlayer(2);
		break;
	case(AttackState::AttackTwice):
		return new SlashSwordAttackPlayer(3);
		break;
	default:
		return new SlashSwordAttackPlayer(1);
		break;
	}
}
