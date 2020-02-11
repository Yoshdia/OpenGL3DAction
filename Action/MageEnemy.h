#pragma once
#include "EnemyBase.h"

/*
@file MageEnemy.h
@brief ボス
*/
class MageEnemy :
	public EnemyBase
{
public:
	/*
	@param _pos 座標
	*/
	MageEnemy(Vector3 _pos);
	~MageEnemy();
	/*
	@brief ゲームオブジェクト停止中に更新、自身にカメラを向けアニメーションを再生、雑魚をPoPさせる
	*/
	void PausingUpdateGameObject()override;
private:
	/*
	@fn 状態(MageActionName)ごとのアクションを行う
	*/
	void UpdateEnemyObject(float _deltaTime)override;

	/*
	@fn アクションを行う対象になるオブジェクト。プレイヤー
	*/
	GameObject* playerObject;
	/*
	@fn 召喚した敵が生存しているか。していないときスタンする。
	*/
	void AliveLoiteringEnemyCheck();
	/*
	@fn 撃破イベント
	*/
	void DeadEvent()override;
	/*
	@fn 攻撃されたとき。召喚した敵が生存しているとき攻撃を喰らわない
	*/
	void HitPlayerAttack(const Vector3& _pairPos,const int& _power)override;
	//プレイヤーが攻撃範囲に入っているか。
	bool attackState;
	//演出中に増え続けるカウント これを参照してカメラの移動位置を決めたりする。
	int directingCount;
	//召喚する近接エネミークラス
	class LoiteringEnemyBase* meleeEnemy;
	//召喚する遠距離エネミークラス
	class LoiteringEnemyBase* rangeEnemy;
	//召喚するエネミーの座標
	Vector3 popLoiteringEnemyPosition;
	//召喚した敵が生存しているとき攻撃を喰らわないようにするためのフラグ
	bool barrier;
	//スタンカウント
	int stanCount;
	//スタンカウントの最大数
	static const int StanCount;
	//攻撃の待機カウント
	int chargeCount;
	//攻撃の待機カウント最大数
	static const int ChargeCount;
	/*
	@enum MageActionName
	このMageEnemyのアクション名
	*/
	enum MageActionName
	{
		//スタン>召喚の待機時間
		SkillCharge,
		//召喚中
		Skill,
		//浮遊しプレイヤーに弾を発射している
		FloatShot,
		//スタン
		Stanning,
		//何もしていない 非攻撃態勢
		None
	};
	//実行中のアクション名
	MageActionName actionName;
	//浮遊、落下、反転などを行うサブクラス
	class DoSubActionMagesChild* subActionClass;
	//このオブジェクトが撃破されたときに消すオブジェクト。ゴールの壁
	GameObject* goalWallObject;
	/*
	@fn プレイヤーに向けて弾を発射する
	@param _target 目標座標
	*/
	void Shot(const Vector3& target);
	//弾の待機カウント
	int shotInterval;
	//弾の待機カウント最大数
	static const int ShotInterval;
	//ボスにダメージが通らないことをアピールするためのシールド画像
	class ParticleObject* guardParticle;
public://ゲッターセッター
	/*
@brief 待機状態から戦闘状態に入る関数　初期化に
*/
	void SetAttackState(GameObject* _playerObject);

	/*
	@fn　このオブジェクトが撃破された時に消す壁　出口
	*/
	void SetGoalWall(GameObject* _wall) { goalWallObject = _wall; }
};

