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
 @brief 敵の基底クラス 敵ごとに決定する変数(体力など)は最下部で宣言
	*/
class EnemyBase abstract :
	public GameObject
{
public:
	/*
	@param meshName mesh名
	*/
	EnemyBase(Vector3 _pos,const std::string& meshName);
	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;
protected:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;

	//このカウントが0以下でないと行動ができない。攻撃時や被弾時にカウントが増える
	int canNotActionTime;

	//生存フラグ
	bool isLive;
	/*
	@fn 死亡時のイベント
	*/
	virtual void DeadEvent() {};

	//アニメーションを管理するクラス
	class AnimationEnemyComponent* animComponent;

	/*
	@fn エネミー固有のUpdate関数、継承先で実装
	*/
	virtual void UpdateEnemyObject(float _deltaTime) {};

	//進行方向
	EnemyMoveDirection moveDirection;
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
	virtual void Attack(float _deltaTime) {};
	//非攻撃態勢 歩行/棒立ち
	void NoAttacking(float _deltaTime);

	/**
	~ 以下継承先で変更が可能 ~(変数の後にある定数は指定がなかった場合のもの) 
	**/
	//初期体力　ゼロになると撃破アニメーションと共に消える
	int hitPoint;
	static const int HitPointMax;
	//攻撃時間
	float attackingTime;
	static const float AttackingTime;
	//被弾時間、被弾時にこの定数がcanNotActionTimeに入る
	float hittingTime;
	static const float HittingTime;
	//歩行速度
	float walkSpeed;
	static const float WalkSpeed;
	//攻撃対象への接近速度
	float approachSpeedRatio;
	static const float ApproachSpeedRatio;
	//発見する範囲
	 float searchRange;
	static const float SearchRange;
	//攻撃の射程距離
	float attackRange;
	static const float AttackRange;
	//次の攻撃までのインターバル最大数
	int attackIntervalCountMax;
	static const int AttackIntervalCount;
};



