#include "MeleeEnemy.h"
#include "SkeltonObjectChecker.h"
#include "EnemyWeapon.h"

 const int MeleeEnemy::HitPointMax=3;
 const float MeleeEnemy::AttackingTime=200;
 const float MeleeEnemy::HittingTime=40;
 const float MeleeEnemy::WalkSpeed=125;
 const float MeleeEnemy::ApproachSpeedRatio=0.8f;
 const float MeleeEnemy::SearchRange=200;
 const float MeleeEnemy::AttackRange=50;
 const int MeleeEnemy::AttackIntervalCount=20;
 
MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	LoiteringEnemyBase(_pos,Vector3(0.5f, 0.5f, 0.5f))
{
	//hitPoint = HitPointMax;
	//attackingTime = AttackingTime;
	//hittingTime = HittingTime;
	//walkSpeed = WalkSpeed;
	//approachSpeedRatio = ApproachSpeedRatio;
	//searchRange = SearchRange;
	//attackRange = AttackRange;
	//attackIntervalCountMax = AttackIntervalCount;
	InstantiateLoiteringEnemyBase();
	hitPoint = 4;
}

MeleeEnemy::~MeleeEnemy()
{
}

void MeleeEnemy::UpdateLoiteringEnemyObject(float _deltaTime)
{
}

void MeleeEnemy::DeadEvent()
{
}

void MeleeEnemy::Attack(float _deltaTime)
{
	Vector3 ataPos = Vector3::Zero;
	ataPos.x = (float)(moveDirection * 60);
	ataPos.y += 40;
	new EnemyWeapon(position+ataPos, Vector3(60,80,20), 30,40);
}

