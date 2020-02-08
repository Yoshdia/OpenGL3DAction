#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerOnce.h
 @brief プレイヤーのコンボ1段目
 メイスを飛ばすクラス。twiceとThirdを統一すべき。
	*/
class AttackPlayerOnce :
	public AttackBase
{
public:
	AttackPlayerOnce();
	~AttackPlayerOnce();
	void Attack(const Vector3& _ownerPosition,const float& _directiron)override;
};

