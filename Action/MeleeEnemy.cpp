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
 const int MeleeEnemy::AttackIntervalCount=20;

MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	EnemyBase(_pos,Vector3(0.5f, 0.5f, 0.5f),"Assets/Model/untitled.gpmesh")
{
	//hitPoint = HitPointMax;
	//attackingTime = AttackingTime;
	//hittingTime = HittingTime;
	//walkSpeed = WalkSpeed;
	//approachSpeedRatio = ApproachSpeedRatio;
	//searchRange = SearchRange;
	//attackRange = AttackRange;
	//attackIntervalCountMax = AttackIntervalCount;
}

MeleeEnemy::~MeleeEnemy()
{
}

void MeleeEnemy::Attack(float _deltaTime)
{
	Vector3 ataPos = Vector3::Zero;
	ataPos.x = moveDirection * 60;
	ataPos.y += 40;
	new EnemyWeapon(position+ataPos, Vector3(60,80,20), 30,40);
}

//void MeleeEnemy::BranchActionChange()
//{
//
//}
//
//void MeleeEnemy::ShuffleCountMax()
//{
//}
