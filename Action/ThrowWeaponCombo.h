#pragma once
#include "ComboMeanPlayerBase.h"
#include "ComboItemThrowWeapon.h"
#include <string>

class ThrowWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	ThrowWeaponCombo();
	~ThrowWeaponCombo();

	void DropMyItem(const Vector3& _pos) { new ComboItemThrowWeapon(_pos); }
	std::string GetComboIconFileName()override { return "Assets/Image/16.png"; }
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

