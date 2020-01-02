#pragma once
#include "EnemyBase.h"

class MageEnemy :
	public EnemyBase
{
public:
	MageEnemy(Vector3 _pos);
	~MageEnemy();
	/*
	@brief ゲームオブジェクト停止中に更新、自身にカメラを向けアニメーションを再生、雑魚をPoPさせる
	*/
	void PausingUpdateGameObject()override;
	/*
	@brief 待機状態から戦闘状態に入る関数　初期化に
	*/
	void SetAttackState();
private:
	void UpdateEnemyObject(float _deltaTime)override;
	void AliveLoiteringEnemyCheck();
	void DeadEvent()override;
	void HitPlayerAttack(const Vector3& _pairPos)override;
	bool attackState;
	int directingCount;
	class LoiteringEnemyBase* meleeEnemy;
	bool barrier;
};

