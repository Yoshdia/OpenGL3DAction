#pragma once
#include "AttackBase.h"

/*
 @file RangeAttackPlayer.h
 @brief �v���C���[�̉������U��
	*/
class RangeAttackPlayer :
	public AttackBase
{
public:
	RangeAttackPlayer();
	~RangeAttackPlayer();
	void Attack(const Vector3& _ownerPosition)override;
};

