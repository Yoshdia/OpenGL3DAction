#pragma once
#include "EnemyBase.h"

class SkeltonObjectChecker;

/*
@file LoiteringEnemyBase.h
@brief 徘徊する敵。プレイヤーを発見し攻撃する状態やプレイヤーを探し続ける状態を持つ。
*/
class LoiteringEnemyBase :
	public EnemyBase
{
public:
	/*
	@param _pos 座標
	@param _scale サイズ
	@param _type エネミーの種類
	@sa　引数はすべてEnemyBaseに渡す
	*/
	LoiteringEnemyBase(Vector3 _pos = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1),  EnemyType _type=EnemyType::MeleeType);
	~LoiteringEnemyBase();
	/*
	@fn このオブジェクトが使いまわしされるときに呼ばれ、パラメータを初期化する
	@param _pos 座標
	@param _hitPoint 体力
	@brief 主にMageEnemyに召喚されるように使用される
	@sa MageEnemy.h
	*/
	void SpawnSummoned(const Vector3& _pos, const int& _hitPoint);
private:
	/*
	@fn プレイヤーに攻撃された
	@brief 体力を減らし、非攻撃態勢だった場合攻撃態勢に移行、ノックバックし被弾中はアクション出来なくなる
	@param _pairPos 衝突相手の座標
	@param _power ダメージ
	*/
	void HitPlayerAttack(const Vector3& _pairPos,const int& _power)override;
	/*
	@fn 撃破イベント
	*/
	void DeadEvent()override;
	/*
	@fn この徘徊エネミー共通の更新関数
	*/
	void UpdateEnemyObject(float _deltaTime)override;
	/*
	@fn 派生クラスの更新関数
	*/
	virtual void UpdateLoiteringEnemyObject(float _deltaTime);
	/*
	@fn 2020/02/08時点で必要無し
	*/
	void PausingUpdateGameObject();

	//足元の座標
	static const Vector3 footPos;
	//足元に地面があるか
	SkeltonObjectChecker* footChecker;
	//エネミーに働く重力の力
	static const float Gravity;
	   
	/*
	@fn アクション変更
	*/
	void ActionChange();
	//一定数まで行くとアクションが変更されるカウント
	int actionChangeCount;
	//アクションが変更されるカウントの最大数。ActionChangeCountMax+乱数で決定
	int actionChangeCountMax;
	//actionChangeCountMaxの初期値
	static const int ActionChangeCountMax;
	/*
	@fnアクションごとの処理
	*/
	void Action(float _deltaTime);
	/*
	@fn 実行中アクションが変更される関数
	*/
	void BranchActionChange();

	/*
	@fn 攻撃態勢の処理
	*/
	void Attacking(float _deltaTime);
	/*
	@fn 攻撃を行う関数
	@sa EnemyWeapon.h
	*/
	virtual void Attack(float _deltaTime);
	/*
	@fn 非攻撃態勢
	*/
	void NoAttacking(float _deltaTime);

	//プレイヤーが離れすぎた場合にワープするためにワープ地点を指定するクラス
	class WarpPointSearchEnemy* warpSearch;
	//ワープ地点指定中かどうか
	bool warpPositonSearching;

	//移動方向の反転ディレイカウント、不自然な挙動を制限する
	int turnWaitCount;
	//移動方向の反転ディレイカウントの最大数
	static const int TurnWaitCountMax;

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

	//攻撃対象を発見した後追跡する範囲。この範囲から対象が出ると追跡を止め歩行/棒立ちモードに変わる
	SkeltonObjectChecker* trackingRange;
	static const Vector3 TrackingRange;

	//テレポートまでの時間
	int teleportChargingTime;


	/*
	@fn ノックバック
	*/
	void NockBack(float _deltaTime);
	//被弾した際のノックバック距離
	static const float NockBackPower;
	//ノックバックの方向、力
	Vector3 nockBackForce;
	//体力の最大値
	static const int HitPointMax;
	//攻撃時間
	static const int AttackingTime;
	//被弾時の硬直
	static const int HittingTime;
	//歩行速度
	static const float WalkSpeed;
	//追跡速度
	static const float ApproachSpeedRatio;
	//索敵範囲
	static const float SearchRange;
	//攻撃開始距離
	static const float AttackRange;
	//攻撃の待機時間
	static const int AttackIntervalCount;
protected:

	//このカウントが0以下でないと行動ができない。攻撃時や被弾時にカウントが増える
	int canNotActionTime;
	/*
	@fn 初期化関数
	@brief 派生クラスごとに変更が行われた定数を別クラスに反映させるために別個に用意
	*/
	void InstantiateLoiteringEnemyBase();

	//攻撃態勢かどうか。false=歩行/棒立ちの非戦闘状態
	bool attackingState;
	//実行中のアクション
	EnemyActions actionName;

	//攻撃時間
	int attackingTime;
	//被弾時間、被弾時にこの定数がcanNotActionTimeに入る
	int hittingTime;
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
	//次の攻撃までのインターバル
	int attackIntervalCount;
};

