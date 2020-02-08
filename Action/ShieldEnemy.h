#pragma once
#include "LoiteringEnemyBase.h"
/*
@file ShieldEnemy.h
@brief 正面からの攻撃をブロックする敵
*/
class ShieldEnemy :
	public LoiteringEnemyBase
{
public:
	/*
@param _pos 座標
*/
	ShieldEnemy(const Vector3& _pos);
	~ShieldEnemy();

private:
	void UpdateLoiteringEnemyObject(float _deltaTime)override;
	void DeadEvent()override;
	void Attack(float _deltaTime)override;

	void HitPlayerAttack(const Vector3& _pairPos, const int& _power)override;

	//初期体力　ゼロになると撃破アニメーションと共に消える
	static const int HitPointMax;
	//攻撃時間
	static const float AttackingTime;
	//被弾時間、被弾時にこの定数がcanNotActionTimeに入る
	static const float HittingTime;
	//歩行速度
	static const float WalkSpeed;
	//攻撃対象への接近速度
	static const float ApproachSpeedRatio;
	//発見する範囲
	static const float SearchRange;
	//攻撃の射程距離
	static const float AttackRange;
	//次の攻撃までのインターバル最大数
	static const int AttackIntervalCount;
};

