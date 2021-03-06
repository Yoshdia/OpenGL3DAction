#pragma once
#include "ComboMeanPlayerBase.h"

/*
@file RotateTripleWeaponCombo.h
@brief ３度回転するメイスを飛ばすコンボ
*/
class RotateTripleWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	RotateTripleWeaponCombo();
	~RotateTripleWeaponCombo();
	void DropMyItem(const Vector3& _pos) { new ComboItemObjectBase(_pos,ComboItemName::RotateComboItem); }
	std::string GetComboIconFileName() override { return "Assets/Image/Item/WoodenClub.png"; }
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

