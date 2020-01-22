#include "RainEnemyWeapon.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"
#include "ColliderComponent.h"

RainEnemyWeapon::RainEnemyWeapon(const Vector3 & _pos):
	GameObject(),
	activeCount(100)
{
	SetPosition(_pos);
	SkeletalMeshComponent* mesh = new SkeletalMeshComponent(this);
	mesh->SetMesh(RENDERER->GetMesh("Assets/Model/Weapon/SK_Blunt_SpikedClub.gpmesh"));
	mesh->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Blunt_SpikedClub.gpskel"));
	tag = Tag::EnemyWeaponTag;
	//SetScale(30);
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

RainEnemyWeapon::~RainEnemyWeapon()
{
}

void RainEnemyWeapon::UpdateGameObject(float _deltaTime)
{
	SetPosition(position + Vector3(0, -5, 0));
	if (activeCount <= 0)
	{
		SetState(State::Dead);
	}
	else
	{
		activeCount--;
	}
}
