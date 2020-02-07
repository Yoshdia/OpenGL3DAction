#include "ThrowWeapon.h"
#include "RotateComponent.h"
#include "ColliderComponent.h"

ThrowWeapon::ThrowWeapon(const Vector3& _pos, const float& _direction, const int& _waitTime, const Tag& _tag) :
	WeaponBase(_pos, _waitTime, 150, _direction, _tag, 1, Vector3(100, 1, 5), 0.08f, "Assets/Model/Weapon/SK_Dual_Blade_Arrow.gpmesh", "Assets/Model/Weapon/SK_Dual_Blade_Arrow.gpskel"),
	velocity(Vector3::Zero),
	collided(false)
{

	if (_direction == 1)
	{
		rotateComponent->SetRotation(90, Vector3::UnitY);
	}
	else
	{
		rotateComponent->SetRotation(-90, Vector3::UnitY);
	}

	if (tag == Tag::PlayerWeaponTag)
	{
		velocity.x = 0;
		velocity.y = 1;
		slow = true;
		SetScale(0.6f);
	}
	else
	{
		velocity.x = (float)(30 * direction);
		velocity.y = 4;
		slow = false;
		SetScale(0.9f);
	}
}


ThrowWeapon::~ThrowWeapon()
{
}

void ThrowWeapon::UpdateWeaponGameObject(float _deltaTime)
{
	if (!collided)
	{
		if (!slow)
		{
			velocity.y -= (27.0f * _deltaTime);
		}
		SetPosition(position + velocity);
	}
	else
	{
		doCollision = false;
	}

	if (activeCount == 8)
	{
		if (tag == Tag::PlayerWeaponTag)
		{
			velocity.x = (float)(30 * direction);
			velocity.y = 5;
			slow = false;
		}
	}
}

void ThrowWeapon::OnTriggerStay(ColliderComponent* _collider)
{
	if (_collider->GetObjectTag() == Tag::GroundTag)
	{
		collided = true;
	}
	if (tag == Tag::PlayerWeaponTag)
	{
		if (_collider->GetObjectTag() == Tag::EnemyTag)
		{
			SetState(State::Dead);
		}	
	}
	else
	{
		if (_collider->GetObjectTag() == Tag::PlayerTag)
		{
			SetState(State::Dead);
		}
	}
}