#pragma once
#include "ComboMeanPlayerBase.h"
#include "ComboItemRotateWeapon.h"

class RotateTripleWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	RotateTripleWeaponCombo();
	~RotateTripleWeaponCombo();
	void DropMyItem(const Vector3& _pos) { new ComboItemRotateWeapon(_pos); }
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

