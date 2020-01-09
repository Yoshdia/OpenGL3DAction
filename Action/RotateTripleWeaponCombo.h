#pragma once
#include "ComboMeanPlayerBase.h"

class RotateTripleWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	RotateTripleWeaponCombo();
	~RotateTripleWeaponCombo();
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

