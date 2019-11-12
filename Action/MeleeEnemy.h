#pragma once
#include "EnemyBase.h"


class MeleeEnemy :
	public EnemyBase
{
public:
	MeleeEnemy(Vector3 _pos);
	~MeleeEnemy();
private:
	void UpdateEnemyObject(float _deltaTime);
};

