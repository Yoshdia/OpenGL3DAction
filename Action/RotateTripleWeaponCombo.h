#pragma once
#include "ComboMeanPlayerBase.h"
#include "ComboItemRotateWeapon.h"
#include <string>

class RotateTripleWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	RotateTripleWeaponCombo();
	~RotateTripleWeaponCombo();
	void DropMyItem(const Vector3& _pos) { new ComboItemRotateWeapon(_pos); }
	std::string GetComboIconFileName() override { return "Assets/Image/16.png"; }
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

