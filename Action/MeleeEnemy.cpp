#include "MeleeEnemy.h"
#include "SkeltonObjectChecker.h"


MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	EnemyBase("Assets/Model/untitled.gpmesh")
{
	SetScale(25);
	SetPosition(_pos);
}


MeleeEnemy::~MeleeEnemy()
{
}

void MeleeEnemy::UpdateEnemyObject(float _deltaTime)
{

}

//void MeleeEnemy::BranchActionChange()
//{
//
//}
//
//void MeleeEnemy::ShuffleCountMax()
//{
//}
