#include "TankEnemy.h"
#include "EnemyWeapon.h"

const int TankEnemy::HitPointMax = 10;
const int TankEnemy::AttackingTime = 200;
const int TankEnemy::HittingTime = 40;
const float TankEnemy::WalkSpeed = 60;
const float TankEnemy::ApproachSpeedRatio = 0.4f;
const float TankEnemy::SearchRange = 200;
const float TankEnemy::AttackRange = 100;
const int TankEnemy::AttackIntervalCount = 20;

TankEnemy::TankEnemy(Vector3 _pos) :
	LoiteringEnemyBase(_pos, Vector3(0.5f, 0.5f, 0.5f),EnemyType::TankType)
{
	hitPoint = HitPointMax;
	attackingTime = AttackingTime;
	hittingTime = HittingTime;
	walkSpeed = WalkSpeed;
	approachSpeedRatio = ApproachSpeedRatio;
	searchRange = SearchRange;
	attackRange = AttackRange;
	attackIntervalCountMax = AttackIntervalCount;
	InstantiateLoiteringEnemyBase();
}

TankEnemy::~TankEnemy()
{
}

void TankEnemy::UpdateLoiteringEnemyObject(float _deltaTime)
{
}

void TankEnemy::DeadEvent()
{
}

void TankEnemy::Attack(float _deltaTime)
{
	Vector3 ataPos = Vector3::Zero;
	ataPos.x = (float)(moveDirection * 120);
	ataPos.y += 40;
	new EnemyWeapon(position + ataPos, Vector3(70, 40, 20), 20, 50);
}
