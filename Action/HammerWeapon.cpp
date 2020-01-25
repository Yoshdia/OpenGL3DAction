#include "HammerWeapon.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "RotateComponent.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"

HammerWeapon::HammerWeapon(const Vector3 & _pos, const int & number, const int & _direction, const int& _lifeCount, const int & _waitTime)
	:WeaponBase(_pos, _waitTime, _lifeCount, _direction,
		Tag::PlayerWeaponTag,3, Vector3(150, 100, 100),0.08f, "Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpmesh", "Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpskel")
{
	SetPosition(_pos + Vector3(((50 * number)*_direction), 0, 0));

	if (_direction == 1)
	{
		rotateComponent->SetRotation(90, Vector3::UnitY);
		rotateComponent->SetRotation(150, Vector3::UnitZ);
		rotateSpeed = -1;
	}
	else
	{
		rotateComponent->SetRotation(-90, Vector3::UnitY);
		rotateComponent->SetRotation(-150, Vector3::UnitZ);
		rotateSpeed = 1;
	}
	rotateComponent->SetRotation(90, Vector3::UnitX);
	doCollision = false;
}

HammerWeapon::~HammerWeapon()
{
}

void HammerWeapon::UpdateWeaponGameObject(float _deltaTime)
{
	rotateComponent->SetRotation(rotateSpeed, Vector3::UnitZ);
	if (activeCount == 15)
	{
		doCollision = true;
		rotateSpeed *= 49;
	}
	if (activeCount == 19)
		rotateSpeed /= 35;
}
