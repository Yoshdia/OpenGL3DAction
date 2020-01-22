#include "RainEnemyWeapon.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"

RainEnemyWeapon::RainEnemyWeapon(const Vector3 & _pos):
	GameObject(),
	activeCount(100)
{
	SetPosition(_pos);
	SkeletalMeshComponent* mesh = new SkeletalMeshComponent(this);
	mesh->SetMesh(RENDERER->GetMesh("Assets/Model/Weapon/SK_Blunt_CinderBlock.gpmesh"));
	mesh->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Blunt_CinderBlock.gpskel"));
	tag = Tag::EnemyWeaponTag;
	//SetScale(30);
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

	RotateComponent* rot = new RotateComponent(this);
	rot->SetRotation(180, Vector3::UnitY);
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
