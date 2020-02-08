#pragma once
#include "EnemyBase.h"
class NoActionEnemyForLoad :
	public EnemyBase
{
public:
	NoActionEnemyForLoad(const Vector3& _pos,const EnemyType& _enemyType,const bool& _leftDirection=false);
	~NoActionEnemyForLoad();

	void UpdateGameObject(float _deltaTime)override;

};

