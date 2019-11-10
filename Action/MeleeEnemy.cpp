#include "MeleeEnemy.h"



MeleeEnemy::MeleeEnemy():
	EnemyBase("Assets/Model/untitled.gpmesh")
{
	SetScale(25);
	SetPosition(Vector3(300, 50, 0));
}


MeleeEnemy::~MeleeEnemy()
{
}

void MeleeEnemy::UpdateEnemyObject(float _deltaTime)
{
}
