#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"
#include "EnemyWeapon.h"
#include "BombParticleEffect.h"
#include "MainCameraObject.h"
#include "WeaponBase.h"
#include "DamageSquareEffect.h"

const int EnemyBase::HitPointMax = 3;

EnemyBase::EnemyBase(Vector3 _pos, Vector3 _scale,EnemyType _type) :
	GameObject(),
	hitPoint(HitPointMax),
	moveDirection(EnemyMoveDirection::right),
	beforeDirection(moveDirection)
{
	SetScale(_scale);
	SetPosition(_pos);
	tag = Tag::EnemyTag;
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(70, 160, 70), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 80, 0));

	rotate = new RotateComponent(this);
	rotate->SetRotation(-90, Vector3::UnitX);

	animComponent = new AnimationEnemyComponent(this,_type);
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

void EnemyBase::OnTriggerEnter(ColliderComponent* _colliderPair)
{
	//プレイヤーの攻撃に接触したとき
	if (_colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		int weaponPower = WeaponBase::SearchWeaponPower(_colliderPair->GetId());
		printf("%d\n", weaponPower);
		new DamageSquareEffect(position+Vector3(0,15,0));
		HitPlayerAttack(_colliderPair->GetPosition(),weaponPower);
	}
}

void EnemyBase::DeadCommonEvent()
{
	SetState(Dead);
	Vector3 effectPos = Vector3(position.x, position.y + 50, position.z);
	new BombParticleEffect(effectPos, Vector3(10, 18, 0),true);
	new BombParticleEffect(effectPos, Vector3(-10, 18, 0),true);
	new BombParticleEffect(effectPos, Vector3(10, 16, 0),true);
	new BombParticleEffect(effectPos, Vector3(10, 12, 0),true);
	new BombParticleEffect(effectPos, Vector3(10, 9, 0),true);
	new BombParticleEffect(effectPos, Vector3(10, 6, 0),true);
	new BombParticleEffect(effectPos, Vector3(10, 3, 0),true);
	new BombParticleEffect(effectPos, Vector3(-10, 16, 0),true);
	new BombParticleEffect(effectPos, Vector3(-10, 12, 0),true);
	new BombParticleEffect(effectPos, Vector3(-10, 9, 0),true);
	new BombParticleEffect(effectPos, Vector3(-10, 6, 0),true);
	new BombParticleEffect(effectPos, Vector3(-10, 3, 0),true);
	DeadEvent();
}

