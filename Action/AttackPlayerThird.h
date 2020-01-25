#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerThird.h
 @brief プレイヤーのコンボ3段目
	*/
class AttackPlayerThird :
	public AttackBase
{
public:
	AttackPlayerThird();
	~AttackPlayerThird();

	void Attack(const Vector3& _ownerPosition,const float& _directiron)override;
};

