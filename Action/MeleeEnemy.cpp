#include "MeleeEnemy.h"



MeleeEnemy::MeleeEnemy():
	EnemyBase("Assets/Model/untitled.gpmesh")
{
	SetScale(25);
	SetPosition(Vector3(300, 200, 0));
}


MeleeEnemy::~MeleeEnemy()
{
}
