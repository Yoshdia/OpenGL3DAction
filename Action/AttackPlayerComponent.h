#pragma once
#include "Component.h"

/*
	 @enum PlayerAttackState
	 Playerの近接コンボの状態
*/
enum PlayerAttackState
{
	NoAttack,
	AttackOnce,
	AttackTwice,
	AttackThird,
	EndAttack,
};

/*
@file AttackPlayerComponent.h
@brief Playerに近接コンボ、遠距離攻撃を行わせるクラス
*/
class AttackPlayerComponent :
	public Component
{
public:
	AttackPlayerComponent(GameObject* _owner, int _updateOrder);
	~AttackPlayerComponent();

	void Update(float _deltaTime);

	/*
	@fn 近距離攻撃
	@brief 入力された際の攻撃を行い、次の攻撃の準備をする
	@param _direction 攻撃時のプレイヤーの向き
	@return プレイヤーに付与する行動不可な時間
	*/
	float Attack(int _direction);
	/*
	@fn 遠距離攻撃
	@brief 入力された際の攻撃を行い、次の攻撃の準備をする
	@param _direction 攻撃時のプレイヤーの向き
	@return プレイヤーに付与する行動不可な時間
	*/
	float RangeAttack(int _direction);
private:
	//近距離攻撃の状態
	PlayerAttackState attackState;
	//遠距離攻撃の回数
	int rangeAttackCount;
	//攻撃を行うクラスへのアドレス
	class AttackBase* attack;
	//近距離攻撃のコンボを次につなげる猶予時間。これが0になるとコンボ状態をリセットする
	float waitTimeForNextAttack;
};

