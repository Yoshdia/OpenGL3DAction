#pragma once
#include "ComboMeanPlayerBase.h"
class TripleSlashSwordCombo :
	public ComboMeanPlayerBase
{
public:
	TripleSlashSwordCombo();
	~TripleSlashSwordCombo();

	void DropMyItem(const Vector3& _pos) { new ComboItemObjectBase(_pos, ComboItemName::SlashSwordComboItem); }
	std::string GetComboIconFileName()override { return "Assets/Image/Item/SharpenedInfantrySword.png"; };
private:
	AttackBase* GetComboAttack(const AttackState& _attackState)override;
};

