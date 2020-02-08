#pragma once
#include "BoneAnimationBaseComponent.h"

class Animation;

/*
@enum EnemyType
@brief 敵の種類
*/
enum EnemyType
{
	//近接攻撃を行う敵
	MeleeType,
	//遠距離攻撃を行う敵
	RangeType,
	//体力が多い敵
	TankType,
	//ボス
	MageType,
	//盾を所持した敵
	ShieldType
};

/*
 @file AnimationEnemyComponent.h
 @brief 基本的な敵全てに対応する、メッシュデータを所持しアニメーションの再生関係の処理を行うクラス
 修正する余地アリ
*/
class AnimationEnemyComponent :
	public BoneAnimationBaseComponent
{
public:
	/*
	@fn　アニメーションやモデルをロードする
	@param _type 敵の種類　ロードするモデルやロードするアニメーションが変わる
	*/
	AnimationEnemyComponent(GameObject * _owner, EnemyType _type, int updateOrder = 100);
	~AnimationEnemyComponent();

	/*
	@fn 全てのアニメーションフラグを倒す
	*/
	void AllFlagReset();
	/*
     @fn animationNameと各フラグを参照しどのアニメーションを再生するかを決定し再生する
	*/
	void UpdateAnimationComponent(float _deltaTime)override;
private:

	//移動
	const Animation* moveAnim;
	//待機
	const Animation* idleAnim;
	//攻撃
	const Animation* attackAnim;
	//召喚
	const Animation* spawnAnim;
	//スタン
	const Animation* stanAnim;
	//アクション
	const Animation* actionAnim;

	/*
	@enum EnemyAnimationName 
	@brief エネミーの共通アクション名
	*/
	enum EnemyAnimationName
	{
		//移動
		Move,
		//待機
		Idle,
		//攻撃
		Attack,
		//召喚
		Spawn,
		//スタン
		Stan,
		//アクション
		Action,
	};
	//現在のアニメーション名
	EnemyAnimationName animationName;

	//移動
	bool move;
	//攻撃
	bool attack;
	//召喚
	bool spawn;
	//スタン
	bool stan;
	//アクション
	bool action;

	//アニメーションの現再生時間
	float animDuration;
	//アニメーションの減少量
	float subAnimDuration;
	//アクションアニメーションの減少量。敵によって減少量が変わるため変数で管理
	float actionAnimationSpeed;
public:	//ゲッターセッター
	/*
	@return アニメーションの残り時間
	*/
	float GetAnimDuration() { return animDuration; }
	/*
	@fn アニメーションフラグをセット
	*/
	void SetMove(bool _move) { move = _move; };
	/*
	@fn アニメーションフラグをセット
	*/
	void SetAttack(bool _attack) { attack = _attack; }
	/*
	@fn アニメーションフラグをセット
	*/
	void SetSpawn(bool _spawn) { spawn = _spawn; }
	/*
	@fn アニメーションフラグをセット
	*/
	void SetStan(bool _stan) { stan = _stan; }
	/*
	@fn アニメーションフラグをセットしアクションアニメーションを再生
	*/
	void SetAction(bool _action);
	/*
	@fn アニメーションフラグをセット
	*/
	void SetSubDuration(float _sub) { subAnimDuration = _sub; }
};

