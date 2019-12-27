#pragma once
#include "EnemyBase.h"

class SkeltonObjectChecker;


class LoiteringEnemyBase :
	public EnemyBase
{
public:
	LoiteringEnemyBase(Vector3 _pos = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
	~LoiteringEnemyBase();

private:
	void UpdateEnemyObject(float _deltaTime)override;
	virtual void UpdateLoiteringEnemyObject(float _deltaTime);

	void HitPlayerAttack(const Vector3& _pairPos)override;
	void DeadEvent()override;

	//攻撃時間
	float attackingTime;
	//被弾時間、被弾時にこの定数がcanNotActionTimeに入る
	float hittingTime;
	//歩行速度
	float walkSpeed;
	//攻撃対象への接近速度
	float approachSpeedRatio;
	//発見する範囲
	float searchRange;
	//攻撃の射程距離
	float attackRange;
	//次の攻撃までのインターバル最大数
	int attackIntervalCountMax;

	//プレイヤーが離れすぎた場合にワープするためにワープ地点を指定するクラス
	class WarpPointSearchEnemy* warpSearch;
	//ワープ地点指定中かどうか
	bool warpPositonSearching;

	//このカウントが0以下でないと行動ができない。攻撃時や被弾時にカウントが増える
	int canNotActionTime;

	//移動方向の反転ディレイカウント、不自然な挙動を制限する
	int turnWaitCount;
	//移動方向の反転ディレイカウントの最大数
	static const int TurnWaitCountMax;
	//足元の座標
	static const Vector3 footPos;
	//足元に地面があるか
	SkeltonObjectChecker* footChecker;
	//エネミーに働く重力の力
	static const float Gravity;

	//進行方向の足元に地面があるか
	SkeltonObjectChecker* forwardDownGroundCheck;
	//forwardDownGroundCheck,forwardGroundCheckのX座標
	static const float GroundCheckPos;

	//forwardDownGroundCheckのY座標
	static const float ForwardDownY;
	//進行方向に壁があるか
	SkeltonObjectChecker* forwardGroundCheck;

	//攻撃対象を発見する範囲
	SkeltonObjectChecker* findingPlayerCheck;


	/*
	 @fn ノックバック
   */
	void NockBack(float _deltaTime);
	//被弾した際のノックバック距離
	static const float NockBackPower;
	//ノックバックの方向、力
	Vector3 nockBackForce;

	//一定数まで行くとアクションが変更されるカウン
	int actionChangeCount;
	//アクションが変更されるカウントの最大数。ActionChangeCountMax+乱数で決定
	int actionChangeCountMax;
	//actionChangeCountMaxの初期値
	static const int ActionChangeCountMax;

	//実行中のアクション
	EnemyActions actionName;
	/*
	@fn アクション変更
	*/
	void ActionChange();
	/*
	@fnアクションごとの処理
	*/
	void Action(float _deltaTime);
	/*
	@fn 実行アクションが変更される関数
	*/
	void BranchActionChange();
	/*
	@fn actionChangeCountMaxの変更を行う関数
	*/
	void ShuffleCountMax();

	//攻撃対象を発見した後追跡する範囲。この範囲から対象が出ると追跡を止め歩行/棒立ちモードに変わる
	SkeltonObjectChecker* trackingRange;
	static const Vector3 TrackingRange;
	//攻撃態勢かどうか。false=歩行/棒立ちの非戦闘状態
	bool attackingState;
	//テレポートまでの時間
	int teleportChargingTime;
	//次の攻撃までのインターバル
	int attackIntervalCount;

	//攻撃態勢 追跡/攻撃
	void Attacking(float _deltaTime);
	virtual void Attack(float _deltaTime);
	//非攻撃態勢 歩行/棒立ち
	void NoAttacking(float _deltaTime);

	static const float AttackingTime;
	static const float HittingTime;
	static const float WalkSpeed;
	static const float ApproachSpeedRatio;
	static const float SearchRange;
	static const float AttackRange;
	static const int AttackIntervalCount;
};

