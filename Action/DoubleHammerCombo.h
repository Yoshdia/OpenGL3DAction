#pragma once
#include "ComboMeanPlayerBase.h"
#include "ComboItemObjectBase.h"

class DoubleHammerCombo :
	public ComboMeanPlayerBase
{
public:
	DoubleHammerCombo();
	~DoubleHammerCombo();
	void DropMyItem(const Vector3& _pos) { new ComboItemObjectBase(_pos,"Assets/Image/16.png",ComboItemName::HammerComboItem); }
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

