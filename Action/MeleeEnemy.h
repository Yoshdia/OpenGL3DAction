#pragma once
#include "EnemyBase.h"


class MeleeEnemy :
	public EnemyBase
{
public:
	MeleeEnemy();
	~MeleeEnemy();
private:
	void UpdateEnemyObject(float _deltaTime);
};

