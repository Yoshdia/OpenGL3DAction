#include "StraightMagicBullet.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"

StraightMagicBullet::StraightMagicBullet(const Vector3 & _shotPosition, const Vector3 & _targetPosition, const int & _waitCount) :
	GameObject(),
	waitCount(_waitCount)
{
	SetPosition(_shotPosition);
	force = Vector3::Normalize(_targetPosition-_shotPosition);
	
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	
	tag = Tag::EnemyWeaponTag;
	colliderComponent = new ColliderComponent(this, 100, Vector3(10, 10, 10), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	colliderComponent->SetDoCollision(false);
}

StraightMagicBullet::~StraightMagicBullet()
{
}

void StraightMagicBullet::UpdateGameObject(float _deltaTime)
{
	if (waitCount <= 0)
	{
		colliderComponent->SetDoCollision(true);
	}
	else
	{
		waitCount--;
	}
	SetPosition(position+(force * 2));
}
