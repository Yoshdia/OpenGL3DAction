#pragma once
#include "GameObject.h"
#include <string>
#include "AnimationEnemyComponent.h"


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
	EnemyBase(Vector3 _pos=Vector3(0,0,0), Vector3 _scale=Vector3(1,1,1), EnemyType _type=EnemyType::MeleeType);

	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;
protected:
	void OnTriggerEnter(ColliderComponent* _colliderPair)override;

	//初期体力　ゼロになると撃破パーティクルと共に消える
	int hitPoint;
	//現在Fの進行方向
	EnemyMoveDirection moveDirection;
	//前Fの進行方向、現Fと異なっていた場合RotateComponentを用いて回転する
	EnemyMoveDirection beforeDirection;

	class RotateComponent* rotate;
	//アニメーションを管理するクラス
	class AnimationEnemyComponent* animComponent;

	/*
	@fn 死亡時のイベント
	*/
	void DeadCommonEvent();
	virtual void DeadEvent() {};

	/*
	@fn エネミー固有のUpdate関数、継承先で実装
	*/
	virtual void UpdateEnemyObject(float _deltaTime) {};
	/*
	@fn 被弾時の処理　ノックバックなど
	*/
	virtual void HitPlayerAttack(const Vector3& _pairPos,const int& _power) {};

	/**
	~ 継承先で変更が行われなかった場合の最大体力 ~
	**/
	static const int HitPointMax;

	GameObject* attackObject;
private:

	Vector3 middlePos;
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
const int LoiteringEnemyBase::HitPointMax = 0;
const float LoiteringEnemyBase::AttackingTime = 0;
const float LoiteringEnemyBase::HittingTime = 0;
const float LoiteringEnemyBase::WalkSpeed = 0;
const float LoiteringEnemyBase::ApproachSpeedRatio = 0;
const float LoiteringEnemyBase::SearchRange = 0;
const float LoiteringEnemyBase::AttackRange = 0;
const int LoiteringEnemyBase::AttackIntervalCount = 0;

hitPoint = HitPointMax;
attackingTime = AttackingTime;
hittingTime = HittingTime;
walkSpeed = WalkSpeed;
approachSpeedRatio = ApproachSpeedRatio;
searchRange = SearchRange;
attackRange = AttackRange;
attackIntervalCount = AttackIntervalCount;

*/