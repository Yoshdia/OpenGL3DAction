#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerOnce.h
 @brief �v���C���[�̃R���{1�i��
	*/
class AttackPlayerOnce :
	public AttackBase
{
public:
	AttackPlayerOnce();
	~AttackPlayerOnce();
	void Attack(const Vector3& _ownerPosition,const int& _directiron)override;
};

