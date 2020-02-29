#include "MeleeEnemy.h"
#include "SkeltonObjectChecker.h"
#include "EnemyWeapon.h"

 const int MeleeEnemy::HitPointMax=6;
 const float MeleeEnemy::AttackingTime=180.0f;
 const float MeleeEnemy::HittingTime=15.0f;
 const float MeleeEnemy::WalkSpeed=200.0f;
 const float MeleeEnemy::ApproachSpeedRatio=0.8f;
 const float MeleeEnemy::SearchRange=200.0f;
 const float MeleeEnemy::AttackRange=100.0f;
 const int MeleeEnemy::AttackIntervalCount=20;

 /*
 @param _pos 座標
 */
MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	LoiteringEnemyBase(_pos,Vector3(0.5f, 0.5f, 0.5f))
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
	ataPos.x = (float)(moveDirection * 50);
	ataPos.y += 40;
	attackObject= new EnemyWeapon(position+ataPos, Vector3(70,80,20), 10,40);
}

void MeleeEnemy::PausingUpdateGameObject()
{
	//ボスの演出中に状態が変化しアニメーションを再生、更新を開始するため手動で更新関数を呼ぶ
	if (pauzingEvent == PauzingEvent::SummonMageEvent)
	{
		ComputeWorldTransform();
		UpdateGameObject(0.016f);
		UpdateComponents(0.016f);
		ComputeWorldTransform();
	}
}

