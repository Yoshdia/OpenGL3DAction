#pragma once
#include "AttackBase.h"

/*
 @file RangeAttackPlayer.h
 @brief ƒvƒŒƒCƒ„[‚Ì‰“‹——£UŒ‚
	*/
class RangeAttackPlayer :
	public AttackBase
{
public:
	RangeAttackPlayer();
	~RangeAttackPlayer();
	void Attack(const Vector3& _ownerPosition)override;
};

