#pragma once
#include "LoiteringEnemyBase.h"
/*
@file RangeEnemy.h
@brief 遠距離攻撃を行う敵
*/
class RangeEnemy :
	public LoiteringEnemyBase
{
public:
	/*
@param _pos 座標
*/
	RangeEnemy(Vector3 _pos);
	~RangeEnemy();

private:
	void UpdateLoiteringEnemyObject(float _deltaTime)override;
	void DeadEvent()override;
	void Attack(float _deltaTime)override;

	//初期体力　ゼロになると撃破アニメーションと共に消える
	static const int HitPointMax;
	//攻撃時間
	static const int AttackingTime;
	//被弾時間、被弾時にこの定数がcanNotActionTimeに入る
	static const int HittingTime;
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

