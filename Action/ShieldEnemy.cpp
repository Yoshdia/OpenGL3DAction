#include "ShieldEnemy.h"
#include "EnemyWeapon.h"
#include "DamageSquareEffect.h"

const int ShieldEnemy::HitPointMax = 6;
const float ShieldEnemy::AttackingTime = 160.0f;
const float ShieldEnemy::HittingTime = 30.0f;
const float ShieldEnemy::WalkSpeed = 80;
const float ShieldEnemy::ApproachSpeedRatio = 0.8f;
const float ShieldEnemy::SearchRange = 200.0f;
const float ShieldEnemy::AttackRange = 60.0f;
const int ShieldEnemy::AttackIntervalCount = 90.0f;

/*
@param _pos 座標
*/
ShieldEnemy::ShieldEnemy(const Vector3& _pos) :
	LoiteringEnemyBase(_pos, Vector3(0.6f, 0.6f, 0.6f), EnemyType::ShieldType)
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

ShieldEnemy::~ShieldEnemy()
{
}

void ShieldEnemy::UpdateLoiteringEnemyObject(float _deltaTime)
{
	if (beforeDirection!=moveDirection)
	{
		canNotActionTime = 180;
		animComponent->SetMove(false);
	}
}

void ShieldEnemy::DeadEvent()
{
}

void ShieldEnemy::Attack(float _deltaTime)
{
	Vector3 ataPos = Vector3::Zero;
	ataPos.x = (float)(moveDirection * 45);
	ataPos.y += 40;
	attackObject= new EnemyWeapon(position + ataPos, Vector3(60, 40, 20), 5, 25);
}

void ShieldEnemy::HitPlayerAttack(const Vector3& _pairPos, const int& _power)
{
	//衝突したオブジェクトの座標を基に自分から見て左右どちらかにあるかを計算しダメージを喰らうか決める
	Vector3 direction = Vector3(0, 0, 0);
	direction = _pairPos - position;
	EnemyMoveDirection guardDirection = EnemyMoveDirection::left;
	if (direction.x > 0)
	{
		guardDirection = EnemyMoveDirection::right;
	}

	if (guardDirection != moveDirection)
	{
		hitPoint -= _power;
		if (!attackingState)
		{
			attackingState = true;
			actionName = EnemyActions::approach;
		}
		//プレイヤーの攻撃の方向を計算しnockBackForceに計算
		double distance = Math::Sqrt((_pairPos.x - position.x) * (_pairPos.x - position.x) + (_pairPos.y - position.y) * (_pairPos.y - position.y));
		Vector3 force = Vector3::Normalize(Vector3((position.x - _pairPos.x), 0, (position.z - _pairPos.z)));
		if (canNotActionTime < hittingTime)
		{
			canNotActionTime = hittingTime;
		}
	}
	else
	{
		//攻撃をブロックしたためエフェクトを再生し専用アニメーションを再生
		new DamageSquareEffect(position + (Vector3(100 * (float)guardDirection, 80.0f, 0)));
		animComponent->SetAction(true);
		animComponent->SetMove(false);
		animComponent->SetSubDuration(0.023f);
		canNotActionTime = 150;
		if (attackObject != nullptr)
		{
		attackObject->SetState(State::Dead);
		}
	}
}
