#pragma once
#include "ComboMeanPlayerBase.h"
class ThrowWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	ThrowWeaponCombo();
	~ThrowWeaponCombo();
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

