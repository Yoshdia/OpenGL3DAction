#include "SlashSwordWeapon.h"
#include "RotateComponent.h"

SlashSwordWeapon::SlashSwordWeapon(const Vector3& _pos, const int& _stage, const float& _direction, const int& _lifeCount, const int& _waitTime):
	WeaponBase(_pos, _waitTime, _lifeCount, _direction,
		Tag::PlayerWeaponTag, 2, Vector3(160, 100, 100), 0.04f, "Assets/Model/Weapon/SK_Blade_BlackKnight.gpmesh", "Assets/Model/Weapon/SK_Blade_BlackKnight.gpskel"),
	rotateSpeed(8.0f)
{
	Vector3 addDistance = Vector3(0, 0, 0);
	rotateDirection = 1;
	switch (_stage)
	{
	case(1):
		addDistance.x += 50;
		break;
	case(2):
		addDistance.x += 100;
		rotateDirection = -1;
		break;
	}
	addDistance *= _direction;
	targetPos = position + addDistance;
	float initRotateX = -150;
	rotateDirection *= _direction;
	if (_direction == -1)
	{
		initRotateX = -30;
	}
	rotateComponent->SetRotation(initRotateX *rotateDirection*_direction, Vector3::UnitX);
	rotateComponent->SetRotation(90, Vector3::UnitY);
	doCollision=false;
}

SlashSwordWeapon::~SlashSwordWeapon()
{
}

void SlashSwordWeapon::UpdateWeaponGameObject(float _deltaTime)
{
	if (activeCount > 8)
	{
		doCollision = false;
		rotateSpeed = 40.0f;
	}
	if (activeCount > 15.0f)
	{
		doCollision = true;
		rotateSpeed = 8.0f;
	}
	if (activeCount > 20.0f)
	{
		doCollision = false;
		rotateSpeed = 1.0f;
	}
	rotateComponent->SetRotation(-rotateSpeed* rotateDirection, Vector3::UnitZ);
	Vector3 add= Vector3((targetPos.x - position.x) * 0.2f, 0, 0);
	SetPosition(position + add);
}
