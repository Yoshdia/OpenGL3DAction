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
	@param _pos 座標
	@param _size サイズ
	@param _enemyType 敵の種類　これを参照しメッシュデータを変更する
	*/
	EnemyBase(Vector3 _pos=Vector3(0,0,0), Vector3 _scale=Vector3(1,1,1), EnemyType _type=EnemyType::MeleeType);

	~EnemyBase();
	/*
	@fn 派生クラスの更新関数を呼び、体力を管理し向きに対して回転を行う
	*/
	void UpdateGameObject(float _deltaTime)override;
protected:
	/*
	@fn プレイヤーに攻撃されたときに、メッシュを発光させその武器の攻撃力を検索し派生クラスの被弾関数へ渡す
	*/
	void OnTriggerEnter(ColliderComponent* _colliderPair)override;

	//初期体力　ゼロになると撃破パーティクルと共に消える
	int hitPoint;
	//現在Fの進行方向
	EnemyMoveDirection moveDirection;
	//前Fの進行方向、現Fと異なっていた場合RotateComponentを用いて回転する
	EnemyMoveDirection beforeDirection;
	//回転を手助けするクラス
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

	/*
	~ 継承先で変更が行われなかった場合の最大体力 ~
	**/
	static const int HitPointMaxDefault;

	//最も最新の、攻撃を行ったオブジェクトへのポインタ。撃破されたときに削除するために所有する
	GameObject* attackObject;

};



/*
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