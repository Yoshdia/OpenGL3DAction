#include "TankEnemy.h"
#include "EnemyWeapon.h"

const int TankEnemy::HitPointMax = 18;
const int TankEnemy::AttackingTime = 200;
const int TankEnemy::HittingTime = 10;
const float TankEnemy::WalkSpeed = 100.0f;
const float TankEnemy::ApproachSpeedRatio = 0.4f;
const float TankEnemy::SearchRange = 200;
const float TankEnemy::AttackRange = 150.0f;
const int TankEnemy::AttackIntervalCount = 20;
/*
@param _pos 座標
*/
TankEnemy::TankEnemy(Vector3 _pos) :
	LoiteringEnemyBase(_pos, Vector3(0.6f, 0.6f, 0.6f),EnemyType::TankType)
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
	ataPos.x = (float)(moveDirection * 80);
	ataPos.y += 40;
	attackObject=new EnemyWeapon(position + ataPos, Vector3(100, 40, 20), 20, 50);
}

/*
@fn ノックバックしない被弾処理
@sa LoiteringEnemyBase::HitPlayerAttack()
*/
void TankEnemy::HitPlayerAttack(const Vector3& _pairPos, const int& _power)
{
	animComponent->SetStartFlash();
	hitPoint -= _power;
	if (!attackingState)
	{
		attackingState = true;
		actionName = EnemyActions::approach;
	}
	//プレイヤーの攻撃の方向を計算しnockBackForceに計算
	double distance = Math::Sqrt((_pairPos.x - position.x) * (_pairPos.x - position.x) + (_pairPos.y - position.y) * (_pairPos.y - position.y));
	if (canNotActionTime < hittingTime)
	{
		canNotActionTime = hittingTime;
	}
}
