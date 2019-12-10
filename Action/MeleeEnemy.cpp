#include "MeleeEnemy.h"
#include "SkeltonObjectChecker.h"

 const int MeleeEnemy::HitPointMax=3;
 const float MeleeEnemy::AttackingTime=200;
 const float MeleeEnemy::HittingTime=40;
 const float MeleeEnemy::WalkSpeed=125;
 const float MeleeEnemy::ApproachSpeedRatio=0.8f;
 const float MeleeEnemy::SearchRange=200;
 const float MeleeEnemy::AttackRange=75;
 const int MeleeEnemy::AttackIntervalCount=60;

MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	EnemyBase(_pos,Vector3(1,1,1),"Assets/Model/untitled.gpmesh")
{
	SetScale(1);
	hitPoint = HitPointMax;
	attackingTime = AttackingTime;
	hittingTime = HittingTime;
	walkSpeed = WalkSpeed;
	approachSpeedRatio = ApproachSpeedRatio;
	searchRange = SearchRange;
	attackRange = AttackRange;
	attackIntervalCountMax = AttackIntervalCount;
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
