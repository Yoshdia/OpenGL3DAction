#pragma once
#include "GameObject.h"


/*
 @file ComboMeanPlayerBase.h
 @brief 1,2,3などのコンボを行うコンボクラスの基底クラス
*/
class ComboMeanPlayerBase
{
public:
	~ComboMeanPlayerBase();
	/*
	@fn AttackPlayerComponentから呼ばれる。攻撃を行う
	@param _pos 攻撃を行う座標
	@param _direction 攻撃を行う向き
	@param &_playerCanNotMoveTime 攻撃後プレイヤーの行動不可時間、硬直を所持する変数への参照
	@param &_waitTimeForNextAttack 攻撃後硬直から次の攻撃までの時間を所持する変数への参照
	*/
	void Attack(const Vector3& _pos, const int& _direction, float& _playerCanNotMoveTime, float& _waitTimeForNextAttack);
	/*
	@fn AttackPlayerComponentから呼ばれる。攻撃状態をリセットする。
	@detail AttackPlayerComponent内で管理されている、次の攻撃までの時間waitTimeForNextAttackがゼロになったときに呼ばれる。
	*/
	void ComboReset() { attackState = AttackState::NoAttack; }
protected:
	/*
	@enum コンボ状態
	*/
	enum AttackState
	{
		//攻撃を行っていない状態
		NoAttack,
		//1段目の攻撃が終了した状態
		AttackOnce,
		//2段目の攻撃が終了した状態
		AttackTwice,
		//3段目の攻撃が終了した状態
		AttackThird,
		//4段目の攻撃が終了した状態
		AttackFourth,
		//すべての攻撃が終了した状態
		EndAttack,
	};
	/*
	@fn 初期コンボ数と最終コンボendAttackStateを初期化する,endAttackStateは継承先クラスで指定
	*/
	ComboMeanPlayerBase(const AttackState& _endAttack);
	//終了コンボ、3段ならAttackThird
	AttackState endAttackState;
private:
	//現在のコンボ
	AttackState attackState;
	//攻撃クラス、ステートパターンを用いて切り替える
	class AttackBase* attack;
	/*
	@fn 継承先クラスで指定、識別子_attackStateをもとに攻撃する
	@param _attackState 現在のコンボを渡す
	@return 攻撃クラス
	*/
	virtual AttackBase* GetComboAttack(const AttackState& _attackState);
};
