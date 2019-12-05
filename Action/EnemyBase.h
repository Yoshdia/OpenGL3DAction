#pragma once
#include "GameObject.h"
#include <string>

class SkeltonObjectChecker;

/*
	 @enum EnemyMoveDirection
	 Enemyが移動する方向
*/
enum EnemyMoveDirection
{
	right = 1,
	left = -1,
};

/*
	 @enum EnemyActions
	 Enemyの共通アクション
*/
enum EnemyActions
{
	//歩行
	walk,
	//棒立ち
	noActive,
	//攻撃対象を発見し接近中
	approach,
	//攻撃中
	attack,
};

/*
 @file EnemyBase.h
 @brief 敵の基底クラス
	*/
class EnemyBase abstract :
	public GameObject
{
public:
	/*
	@param meshName mesh名
	*/
	EnemyBase(const std::string& meshName);
	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;
protected:
	int canNotActionTime;
	class AnimationEnemyComponent* animComponent;
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;
	/*
	@fn エネミー固有の関数、継承先で実装
	*/
	virtual void UpdateEnemyObject(float _deltaTime) {};

	//進行方向
	EnemyMoveDirection moveDirection;
	//移動方向の反転ディレイカウント、不自然な挙動を制限する
	int turnWaitCount;
	//移動方向の反転ディレイカウントの最大数
	static const int TurnWaitCountMax;
	//歩行速度
	static const float WalkSpeed;
	//攻撃対象への接近速度
	static const float ApproachSpeedRatio;
	//歩行速度の上限値
	static const float WalkSpeedLimit;

	static const Vector3 footPos;
	//足元に地面があるか
	SkeltonObjectChecker* footChecker;
	//エネミーに働く重力の力
	static const float Gravity;
	//重力の上限値
	static const float GravityLimit;

	//進行方向の足元に地面があるか
	SkeltonObjectChecker* forwardDownGroundCheck;
	//forwardDownGroundCheck,forwardGroundCheckのX座標
	static const float GroundCheckPos;

	//forwardDownGroundCheckのY座標
	static const float ForwardDownY;
	//進行方向に壁があるか
	SkeltonObjectChecker* forwardGroundCheck;

	//発見する範囲
	static const float SearchRange;
	//攻撃対象を発見する範囲
	SkeltonObjectChecker* findingPlayerCheck;
	//攻撃を開始する射程距離
	float attackRange;

	/*
	  @fn ノックバック
	*/
	void NockBack(float _deltaTime);
	//被弾した際のノックバック距離
	static const float NockBackPower;
	//ノックバックの方向、力
	Vector3 nockBackForce;

	//actionChangeCountMaxの初期値
	static const int DefaultActionChangeCountMax;
	//一定数まで行くとアクションが変更されるカウントとその最大数
	int actionChangeCount;
	int actionChangeCountMax;
	//攻撃対象を発見してないとき、移動と棒立ちを切り替える時間の共有カウント
	int defaultActionChangeCountMax;

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
	virtual void BranchActionChange();
	/*
	@fn actionChangeCountMaxの変更を行う関数
	*/
	virtual void ShuffleCountMax();

	//攻撃対象を発見した後追跡する範囲。この範囲から対象が出ると追跡を止め歩行/棒立ちモードに変わる
	SkeltonObjectChecker* trackingRange;
	static const Vector3 TrackingRange;
	//攻撃態勢かどうか。false=歩行/棒立ちの非戦闘状態
	bool attackingState;
	//テレポートまでの時間
	int teleportChargingTime;
	static const float AttackRange;
	int attackIntervalCount;
	static const int AttackIntervalCount;

	//攻撃態勢 追跡/攻撃
	void Attacking(float _deltaTime);
	//非攻撃態勢 歩行/棒立ち
	void NoAttacking(float _deltaTime);
};



