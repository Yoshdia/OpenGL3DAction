#pragma once
#include "GameObject.h"
#include <string>


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
	EnemyBase(Vector3 _pos=Vector3(0,0,0), Vector3 _scale=Vector3(1,1,1));

	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;
protected:
	/**
	~ 以下継承先で変更が可能 ~(private内にある定数は指定がなかった場合のもの)
	**/
	//初期体力　ゼロになると撃破アニメーションと共に消える
	int hitPoint;

	//現在Fの進行方向
	EnemyMoveDirection moveDirection;
	//前Fの進行方向、現Fと異なっていた場合RotateComponentを用いて回転する
	EnemyMoveDirection beforeDirection;

	void OnTriggerEnter(ColliderComponent* colliderPair)override;
	/*
	@fn 被弾時の処理　ノックバックなど
	*/
	virtual void HitPlayerAttack(const Vector3& _pairPos) {};

	class RotateComponent* rotate;

	/*
	@fn 死亡時のイベント
	*/
	virtual void DeadEvent() {};
	void DeadCommonEvent();

	//アニメーションを管理するクラス
	class AnimationEnemyComponent* animComponent;

	/*
	@fn エネミー固有のUpdate関数、継承先で実装
	*/
	virtual void UpdateEnemyObject(float _deltaTime) {};

	/**
	~ protected内の変数に継承先で変更が行われなかった場合の定数 ~
	**/
	static const int HitPointMax;
};



/**
~ コピペ用テンプレート ~
**/
//.h用
/*
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
*/
//.cpp用
/*
const int MeleeEnemy::HitPointMax = 0;
const float MeleeEnemy::AttackingTime = 0;
const float MeleeEnemy::HittingTime = 0;
const float MeleeEnemy::WalkSpeed = 0;
const float MeleeEnemy::ApproachSpeedRatio = 0;
const float MeleeEnemy::SearchRange = 0;
const float MeleeEnemy::AttackRange = 0;
const int MeleeEnemy::AttackIntervalCount = 0;

hitPoint = HitPointMax;
attackingTime = AttackingTime;
hittingTime = HittingTime;
walkSpeed = WalkSpeed;
approachSpeedRatio = ApproachSpeedRatio;
searchRange = SearchRange;
attackRange = AttackRange;
attackIntervalCount = AttackIntervalCount;
*/