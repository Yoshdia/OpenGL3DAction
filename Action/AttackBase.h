#pragma once
#include "Math.h"

/*
 @file AttackBase.h
 @brief プレイヤーの攻撃基底クラス。Attack内の関数で攻撃内容を決定する
	*/
class AttackBase abstract
{
public:
	AttackBase();
	~AttackBase();
	/*
	@fn 攻撃内容
	@param _ownerPosition 攻撃した座標
	@param _directiron 攻撃する向き
	*/
	virtual void Attack(const Vector3& _ownerPosition,const float& _directiron) {};

protected:
	//派生クラスで決定する値。派生クラスの攻撃を行った際にプレイヤーに発生する移動不可時間(硬直)
	float canNotActionTime;
	//派生クラスで決定する値。次の攻撃に派生させる猶予時間(コンボ猶予時間)
	float waitTimeForNextAttack;
public://ゲッターセッター
	/*
	@return 攻撃直後のアクションを受け付けない時間。硬直。
	*/
	float GetCanNotActionTime() { return canNotActionTime; }
	/*
	@return 攻撃から次の攻撃に繋げることができる時間。コンボ猶予
	*/
	float GetWaitTimeForNextAttack() { return waitTimeForNextAttack; }
};

