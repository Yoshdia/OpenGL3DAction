#include "ShieldEnemy.h"
#include "EnemyWeapon.h"
#include "DamageSquareEffect.h"

const int ShieldEnemy::HitPointMax = 6;
const float ShieldEnemy::AttackingTime = 300;
const float ShieldEnemy::HittingTime = 30.0f;
const float ShieldEnemy::WalkSpeed = 80;
const float ShieldEnemy::ApproachSpeedRatio = 0.8f;
const float ShieldEnemy::SearchRange = 200.0f;
const float ShieldEnemy::AttackRange = 50.0f;
const int ShieldEnemy::AttackIntervalCount = 60;

/*
@param _pos ���W
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
}

void ShieldEnemy::DeadEvent()
{
}

void ShieldEnemy::Attack(float _deltaTime)
{
	Vector3 ataPos = Vector3::Zero;
	ataPos.x = (float)(moveDirection * 60);
	ataPos.y += 40;
	attackObject= new EnemyWeapon(position + ataPos, Vector3(60, 80, 20), 30, 40);
}

void ShieldEnemy::HitPlayerAttack(const Vector3& _pairPos, const int& _power)
{
	//�Փ˂����I�u�W�F�N�g�̍��W����Ɏ������猩�č��E�ǂ��炩�ɂ��邩���v�Z���_���[�W����炤�����߂�
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
		//�v���C���[�̍U���̕������v�Z��nockBackForce�Ɍv�Z
		double distance = Math::Sqrt((_pairPos.x - position.x) * (_pairPos.x - position.x) + (_pairPos.y - position.y) * (_pairPos.y - position.y));
		Vector3 force = Vector3::Normalize(Vector3((position.x - _pairPos.x), 0, (position.z - _pairPos.z)));
		canNotActionTime = hittingTime;
	}
	else
	{
		//�U�����u���b�N�������߃G�t�F�N�g���Đ�����p�A�j���[�V�������Đ�
		new DamageSquareEffect(position + (Vector3(100 * (float)guardDirection, 80.0f, 0)));
		animComponent->SetAction(true);
		animComponent->SetSubDuration(0.023f);
		canNotActionTime = 150;
	}
}
