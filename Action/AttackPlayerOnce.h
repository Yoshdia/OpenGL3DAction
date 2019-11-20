#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerOnce.h
 @brief プレイヤーのコンボ1段目
	*/
class AttackPlayerOnce :
	public AttackBase
{
public:
	AttackPlayerOnce();
	~AttackPlayerOnce();
	void Attack(const Vector3& _ownerPosition,const int& _directiron)override;
};

