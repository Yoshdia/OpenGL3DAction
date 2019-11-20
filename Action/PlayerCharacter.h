#pragma once
#include "GameObject.h"

struct InputState;

/*
 @file PlayerCharacter.h
 @brief プレイヤー
	*/
class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState & _keyState) override;
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	//アニメーション
	class AnimationPlayerComponent* animationComponent;
	//足の裏、着地しているかどうかを検知する
	class SkeltonObjectChecker* footChecker;

	//入力による行動が制限される時間　主にAttackPlayerComponentの攻撃アクションから受け取る
	float canNotActionTime;

	//移動力
	Vector3 velocity;

	/*
	@fn 攻撃
	@param _animState 近接攻撃、遠距離攻撃のどちらを行うか
	*/
	void Attack(PlayerAnimationState _animState);
	//近接コンボ、遠距離攻撃を行うクラス
	class AttackPlayerComponent* attack;
	//近接攻撃ボタンの入力フラグ
	bool attackBottonInput;
	//遠距離攻撃ボタンの入力フラグ
	bool rangeAttackBottonInput;

	/*
	@fn 左右移動
	@brief 左右の入力情報をもとにvelocityへ値を代入しアニメーションを再生する
	*/
	void Move();
	//入力方向、左...-1 右...1
	float inputDirection;
	//移動速度
	static const float MoveSpeed;

	/*
	@fn ジャンプ
	*/
	void Jump();
	//ジャンプボタンの入力フラグ
	bool jumpBottonInput;
	//ジャンプ力 
	static const float JumpPower;

	/*
	@fn 重力
	*/
	void Gravity();
	//重力
	static const float GravityPower;

	/*
	@fn 摩擦
	@brief 左右方向へのvelocityへ摩擦を付与
	*/
	void Friction();
	//左右方向への摩擦
	static const float MoveFriction;
};

