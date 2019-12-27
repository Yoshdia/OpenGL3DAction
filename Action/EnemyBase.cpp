#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"
#include "AnimationEnemyComponent.h"
#include "EnemyWeapon.h"
#include "ParticleEffect.h"
#include "MainCameraObject.h"

const int EnemyBase::HitPointMax = 3;
const float EnemyBase::AttackingTime = 30;
const float EnemyBase::HittingTime = 40.0f;
const float EnemyBase::WalkSpeed = 125;
const float EnemyBase::ApproachSpeedRatio = 0.8f;
const float EnemyBase::SearchRange = 200;
const float EnemyBase::AttackRange = 75.0f;
const int EnemyBase::AttackIntervalCount = 120;


EnemyBase::EnemyBase(Vector3 _pos, Vector3 _scale) :
	GameObject(),
	moveDirection(EnemyMoveDirection::right),
	beforeDirection(moveDirection),
	hitPoint(HitPointMax)
{
	SetScale(_scale);
	SetPosition(_pos);
	tag = Tag::EnemyTag;
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(10, 10, 10), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	rotate = new RotateComponent(this);
	rotate->SetRotation(-90, Vector3::UnitX);

	animComponent = new AnimationEnemyComponent(this);
	animComponent->SetMove(true);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::UpdateGameObject(float _deltaTime)
{
	if (hitPoint <= 0)
	{
		//撃破されたのでメインカメラの注視位置を1F変更し衝撃のように見せる
		mainCamera->SetViewMatrixLerpObject(Vector3(0, 0, 0), position);
		//敵クラスごとの撃破イベント
		DeadCommonEvent();
		return;
	}
	//敵クラスごとの更新
	UpdateEnemyObject(_deltaTime);

	//前Fと向きが異なっていた場合回転
	if (beforeDirection != moveDirection)
	{
		rotate->SetRotation(180, Vector3::UnitY);
		beforeDirection = moveDirection;
	}
}

void EnemyBase::OnTriggerEnter(ColliderComponent* colliderPair)
{
	//プレイヤーの攻撃に接触したとき
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		HitPlayerAttack(colliderPair->GetPosition());
		hitPoint--;
	}
}

void EnemyBase::DeadCommonEvent()
{
	SetState(Dead);
	Vector3 effectPos = Vector3(position.x, position.y + 50, position.z);
	new ParticleEffect(effectPos, Vector3(10, 18, 0));
	new ParticleEffect(effectPos, Vector3(-10, 18, 0));
	new ParticleEffect(effectPos, Vector3(10, 16, 0));
	new ParticleEffect(effectPos, Vector3(10, 12, 0));
	new ParticleEffect(effectPos, Vector3(10, 9, 0));
	new ParticleEffect(effectPos, Vector3(10, 6, 0));
	new ParticleEffect(effectPos, Vector3(10, 3, 0));
	new ParticleEffect(effectPos, Vector3(-10, 16, 0));
	new ParticleEffect(effectPos, Vector3(-10, 12, 0));
	new ParticleEffect(effectPos, Vector3(-10, 9, 0));
	new ParticleEffect(effectPos, Vector3(-10, 6, 0));
	new ParticleEffect(effectPos, Vector3(-10, 3, 0));
	DeadEvent();
}

