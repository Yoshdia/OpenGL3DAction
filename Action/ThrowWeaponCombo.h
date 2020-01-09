#pragma once
#include "ComboMeanPlayerBase.h"

#include "ComboItemThrowWeapon.h"

class ThrowWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	ThrowWeaponCombo();
	~ThrowWeaponCombo();

	void DropMyItem(const Vector3& _pos) { new ComboItemThrowWeapon(_pos); }
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

