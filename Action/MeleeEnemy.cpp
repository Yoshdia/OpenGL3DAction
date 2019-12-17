#include "MeleeEnemy.h"
#include "SkeltonObjectChecker.h"
#include "EnemyWeapon.h"

 const int MeleeEnemy::HitPointMax=3;
 const float MeleeEnemy::AttackingTime=200;
 const float MeleeEnemy::HittingTime=40;
 const float MeleeEnemy::WalkSpeed=125;
 const float MeleeEnemy::ApproachSpeedRatio=0.8f;
 const float MeleeEnemy::SearchRange=200;
 const float MeleeEnemy::AttackRange=75;
 const int MeleeEnemy::AttackIntervalCount=60;

MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	EnemyBase(_pos,Vector3(0.5f, 0.5f, 0.5f),"Assets/Model/untitled.gpmesh")
{
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

void MeleeEnemy::Attack(float _deltaTime)
{
	Vector3 ataPos = Vector3::Zero;
	ataPos.x = moveDirection * 60;
	ataPos.y += 60;
	new EnemyWeapon(position+ataPos, Vector3(30,80,20), 60,10);
}

//void MeleeEnemy::BranchActionChange()
//{
//
//}
//
//void MeleeEnemy::ShuffleCountMax()
//{
//}
