#include "MeleeEnemy.h"
#include "SkeltonObjectChecker.h"


MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	EnemyBase(_pos,"Assets/Model/untitled.gpmesh")
{
	SetScale(1);
	SetPosition(_pos);


}

MeleeEnemy::~MeleeEnemy()
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
