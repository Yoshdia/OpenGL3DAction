#pragma once
#include "ComboMeanPlayerBase.h"

/*
@file DoubleHammerCombo.h
@brief ハンマーで二度殴りつけるコンボ
*/
class DoubleHammerCombo :
	public ComboMeanPlayerBase
{
public:
	DoubleHammerCombo();
	~DoubleHammerCombo();
	void DropMyItem(const Vector3& _pos) { new ComboItemObjectBase(_pos,ComboItemName::HammerComboItem); }
	std::string GetComboIconFileName()override { return "Assets/Image/Item/WarHammer.png"; };
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

