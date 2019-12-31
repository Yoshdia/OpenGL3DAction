#pragma once


#include "EnemyBase.h"
class MageEnemy :
	public EnemyBase
{
public:
	MageEnemy(Vector3 _pos);
	~MageEnemy();

private:
	void UpdateEnemyObject(float _deltaTime)override;
	void DeadEvent()override;
	void HitPlayerAttack(const Vector3& _pairPos)override;
};

