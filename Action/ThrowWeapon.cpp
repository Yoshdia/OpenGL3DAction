#include "ThrowWeapon.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"


ThrowWeapon::ThrowWeapon(const Vector3& _pos, const int& _direction) :
	lifeCount(240),
	direction(_direction)
{
	SetPosition(_pos);
	tag = Tag::PlayerWeaponTag;
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));
}


ThrowWeapon::~ThrowWeapon()
{
}

void ThrowWeapon::UpdateGameObject(float _deltaTime)
{
	if (lifeCount < 0)
	{
		lifeCount = 0;
		SetState(State::Dead);
	}
	else
	{
		lifeCount++;
		SetPosition(Vector3(position.x += (10* direction), position.y, position.z));
	}
}
