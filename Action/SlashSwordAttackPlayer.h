#pragma once
#include "AttackBase.h"

/*
@file SlashSwordAttackPlayer.h
@brief ���Ő؂����U��
*/
class SlashSwordAttackPlayer :
	public AttackBase
{
public:
	SlashSwordAttackPlayer(const float& _number);
	~SlashSwordAttackPlayer();
	void Attack(const Vector3& _ownerPosition, const float& _direction)override;
private:
	float number;
};

