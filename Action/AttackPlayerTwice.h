#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerTwice.h
 @brief プレイヤーのコンボ2段目
	*/
class AttackPlayerTwice final :
	public AttackBase
{
public:
	AttackPlayerTwice();
	~AttackPlayerTwice();

	void Attack(const Vector3& _ownerPosition,const float& _directiron)override;
};

