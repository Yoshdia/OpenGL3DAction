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

const int EnemyBase::HitPointMaxDefault = 3;

/*
@param _pos 座標
@param _size サイズ
@param _enemyType 敵の種類　これを参照しメッシュデータを変更する
*/
EnemyBase::EnemyBase(Vector3 _pos, Vector3 _scale, EnemyType _type) :
	GameObject(),
	hitPoint(HitPointMaxDefault),
	moveDirection(EnemyMoveDirection::right),
	beforeDirection(moveDirection),
	attackObject(nullptr)
{
	SetScale(_scale);
	SetPosition(_pos);
	tag = Tag::EnemyTag;
	//衝突判定を置く中心座標(ゼロは足元)
	Vector3  collisionPos = Vector3(20, 80, 0);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(120, 160, 70), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, collisionPos);
	//モデルの向きを変更(デフォルトは正面)
	rotate = new RotateComponent(this);
	rotate->SetRotation(-90, Vector3::UnitX);
	//エネミーごとの識別子を基にアニメーションクラスを生成
	animComponent = new AnimationEnemyComponent(this, _type);
	animComponent->SetMove(true);
}

EnemyBase::~EnemyBase()
{
}

/*
@fn 派生クラスの更新関数を呼び、体力を管理し向きに対して回転を行う
*/
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

/*
@fn プレイヤーに攻撃されたときに、メッシュを発光させその武器の攻撃力を検索し派生クラスの被弾関数へ渡す
*/
void EnemyBase::OnTriggerEnter(ColliderComponent* _colliderPair)
{
	//プレイヤーの攻撃に接触したとき
	if (_colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		int weaponPower = WeaponBase::SearchWeaponPower(_colliderPair->GetId());
		printf("WeaponPower :: %d \n", weaponPower);
		HitPlayerAttack(_colliderPair->GetPosition(), weaponPower);
	}
}

/*
@fn 死亡時のイベント
*/
void EnemyBase::DeadCommonEvent()
{
	if (attackObject != nullptr)
	{
		attackObject->SetState(State::Dead);
	}
	SetState(Dead);
	DeadEvent();
	//爆発するようなエフェクトを生成
	Vector3 effectPos = Vector3(position.x, position.y + 50, position.z);
	new BombParticleEffect(effectPos, Vector3(10, 20, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 20, 0));
	new BombParticleEffect(effectPos, Vector3(10, 18, 0));
	new BombParticleEffect(effectPos, Vector3(10, 14, 0));
	new BombParticleEffect(effectPos, Vector3(10, 11, 0));
	new BombParticleEffect(effectPos, Vector3(10, 8, 0));
	new BombParticleEffect(effectPos, Vector3(10, 5, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 18, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 14, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 1, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 8, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 5, 0));
}

