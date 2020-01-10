#include "ThrowWeapon.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"

ThrowWeapon::ThrowWeapon(const Vector3& _pos, const int& _direction, const int& _waitTime, const Tag& _tag) :
	WeaponBase(_pos, _waitTime, 150, _direction, _tag,1, Vector3(100, 30, 5), "Assets/Model/Weapon/SK_Dual_Blade_Arrow.gpmesh", "Assets/Model/Weapon/SK_Dual_Blade_Arrow.gpskel"),
	velocity(Vector3::Zero),
	collided(false)
{
	SetScale(0.9f);

	if (_direction == 1)
		rotateComponent->SetRotation(90, Vector3::UnitY);

	velocity.x = (float)(30 * direction);
	velocity.y = 4;
}


ThrowWeapon::~ThrowWeapon()
{
}

void ThrowWeapon::UpdateWeaponGameObject(float _deltaTime)
{
	if (!collided)
	{
		velocity.y -= (27.0*_deltaTime);
		SetPosition(position + velocity);
	}
}

void ThrowWeapon::OnTriggerStay(ColliderComponent * _collider)
{
	if (_collider->GetObjectTag() == Tag::GroundTag)
	{
		collided = true;
	}
}