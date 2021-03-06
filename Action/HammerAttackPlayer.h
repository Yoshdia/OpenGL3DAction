#pragma once
#include "AttackBase.h"

/*
@file HammerAttackPlayer.h
@brief ハンマーで攻撃する
*/
class HammerAttackPlayer :
	public AttackBase
{
public:
	HammerAttackPlayer(const float& _number);
	~HammerAttackPlayer();
	void Attack(const Vector3& _ownerPosition, const float& _direction)override;
private:
	float number;
};

