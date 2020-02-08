#include "RangeEnemy.h"
#include "ThrowWeapon.h"
#include "AnimationEnemyComponent.h"

const int RangeEnemy::HitPointMax = 5;
const int RangeEnemy::AttackingTime = 300;
const int RangeEnemy::HittingTime = 40;
const float RangeEnemy::WalkSpeed = 50;
const float RangeEnemy::ApproachSpeedRatio = 0.4f;
const float RangeEnemy::SearchRange = 500;
const float RangeEnemy::AttackRange = 500;
const int RangeEnemy::AttackIntervalCount = 20;

/*
@param _pos ç¿ïW
*/
RangeEnemy::RangeEnemy(Vector3 _pos):
	LoiteringEnemyBase(_pos, Vector3(0.8f, 0.8f, 0.8f),EnemyType::RangeType)
{
	hitPoint = HitPointMax;
	attackingTime = AttackingTime;
	hittingTime = HittingTime;
	walkSpeed = WalkSpeed;
	approachSpeedRatio = ApproachSpeedRatio;
	searchRange = SearchRange;
	attackRange = AttackRange;
	attackIntervalCount = AttackIntervalCount;
	InstantiateLoiteringEnemyBase();
}

RangeEnemy::~RangeEnemy()
{
}

void RangeEnemy::UpdateLoiteringEnemyObject(float _deltaTime)
{
}

void RangeEnemy::DeadEvent()
{
}

void RangeEnemy::Attack(float _deltaTime)
{
	Vector3 attackPos = Vector3::Zero;
	attackPos.x = (float)(moveDirection * 60);
	attackPos.y += 40;
	attackObject= new ThrowWeapon(attackPos+position, (float)moveDirection,100,Tag::EnemyWeaponTag);
}
