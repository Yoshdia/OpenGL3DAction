#pragma once
#include "ComboMeanPlayerBase.h"

/*
@file ThrowWeaponCombo.h
@brief ñÓÇÃÇÊÇ§Ç»ïêäÌÇîÚÇŒÇ∑
*/
class ThrowWeaponCombo :
	public ComboMeanPlayerBase
{
public:
	ThrowWeaponCombo();
	~ThrowWeaponCombo();

	void DropMyItem(const Vector3& _pos) { new ComboItemObjectBase(_pos,ComboItemName::ThrowComboItem); }
	std::string GetComboIconFileName()override { return "Assets/Image/Item/MarauderBow.png"; }
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

