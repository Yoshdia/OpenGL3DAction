#pragma once
#include "AttackBase.h"

/*
@file HammerAttackPlayer.h
@brief ƒnƒ“ƒ}[‚ÅUŒ‚‚·‚é
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

