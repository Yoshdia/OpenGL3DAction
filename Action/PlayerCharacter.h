#pragma once
#include "GameObject.h"
#include "AnimationPlayerComponent.h"

struct InputState;


/*
 @file PlayerCharacter.h
 @brief プレイヤー
	*/
class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter(const Vector3& _pos);
	~PlayerCharacter();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState) override;

	void FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag& _pairTag)override;
	void PausingUpdateGameObject();
	bool GetGameEnd();
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	//アニメーション
	class AnimationPlayerComponent* animationComponent;
	//足の裏、床(Ground)を対象に着地しているかどうかを検知する
	class SkeltonObjectChecker* footChecker;
	//足の裏、薄い床(ThinGround)を対象に着地しているかどうかを検知する
	class SkeltonObjectChecker* thinChecker;

	class SkeltonObjectChecker* headRoofChecker;

	//入力による行動が制限される時間　主にAttackPlayerComponentの攻撃アクションから受け取る
	float canNotActionTime;

	//向き
	int direction;

	//移動力
	Vector3 velocity;

	/*
	@fn プレイヤーが行うアクション
	*/
	void Actions(float _deltaTime,const bool& _noGround);

	//近接コンボ、遠距離攻撃を行うクラス
	class AttackPlayerObject* attack;
	//近接攻撃ボタンの入力フラグ
	bool attackBottonInput;
	//遠距離攻撃ボタンの入力フラグ
	bool rangeAttackBottonInput;

	/*
	@fn 防御
	*/
	//void Guard();
	////防御のための盾の生成、ガード済みの攻撃の管理を行うクラス
	//class GuardPlayerComponent* guardComponent;
	////ガードボタンの入力フラグ
	//bool guardBottonInput;
	bool avoidanceBottonInput;
	void Avoidance();
	void AcoidanceIntervalDown();
	bool avoidancing;
	int avoidanceInterval;
	static const int AvoidanceInvincible;
	static const int AvoidanceInterval;
	/*
	@fn 左右移動
	@brief 左右の入力情報をもとにvelocityへ値を代入しアニメーションを再生する
	*/
	void Move(float _deltaTime);
	//入力方向、左...-1 右...1
	int inputDirection;
	//移動速度
	static const float MoveSpeed;

	/*
	@fn 薄い床をすり抜ける
	@brief 下方向への入力の直後ニュートラルにするなどの操作がありまたその直後に下方向への入力があったらフラグをたてる(下・下)
	*/
	void SkeletonThinGround();

	//下方向への入力情報、薄い床の上からそれを通り抜ける際に使用
	float inputUnderDirection;
	//下方向への入力が行われた直後に下方向への入力が無くなったときに建つフラグ
	bool noInputForUnderDirection;
	//薄い床の上からそれを通り抜けるための入力に対するカウント
	int inputUnderCount;
	//薄い床の上からそれを通り抜けるための入力に対するカウントのリセット値
	static const int InputUnderCountMax;
	//薄い床をすり抜ける実行フラグ
	bool doSkeletonThinGround;


	/*
	@fn ジャンプ
	*/
	void Jump();
	//ジャンプボタンの入力フラグ
	bool jumpBottonInput;
	//ジャンプ力 
	static const float JumpPower;
	//ジャンプ後の浮上中か　浮上中のみ接触判定を行わない床があるため使用
	bool isFloating;
	//ThinGroundオブジェクトに接触しているか
	bool isThinGroundCollision;

	/*
	@fn 重力
	*/
	void Gravity(float _deltaTime);
	//重力
	static const float GravityPower;

	/*
	@fn 摩擦
	@brief 左右方向へのvelocityへ摩擦を付与
	*/
	void Friction(float _friction);
	//左右方向への摩擦
	static const float MoveFriction;

	static const float DownFriction;

	/*
	@fn 被弾
	@brief HPが減少し無敵時間を追加する
	*/
	void HitAttack();
	/*
	@fn 無敵時間の管理
	*/
	void Invincible();
	//無敵か
	bool invincible;
	//無敵時間
	int invincibleCount;
	//無敵時間の最大数
	static const int InvincibleCount;

	int hitPoint;
	bool isLive;

	int candleHealingInterval;
	static const int CandleHealingInterval;
	void CandleHealingIntervalDown();
};

