#include "WeaponRotationAnimationPlayer.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"

WeaponRotationAnimationPlayer::WeaponRotationAnimationPlayer(const Vector3& _pos, const int& _direction, const int& _waitCount, const int& _lifeCount, const int& _moveDistanceStage) :
	WeaponBase(_pos, _waitCount, _lifeCount, _direction,
		Tag::PlayerWeaponTag,3, Vector3(75, 75, 75),0.02f, "Assets/Model/Weapon/SK_Blunt_SpikedClub.gpmesh", "Assets/Model/Weapon/SK_Blunt_SpikedClub.gpskel"),
	rotateSpeed(50),
	rotateSpeedSub(0.45f)
{
	SetScale(0.5f);
	Vector3 addDistance = Vector3(0, 0, 0);
	switch (_moveDistanceStage)
	{
	case(0):addDistance.x += 60; break;
	case(1):addDistance.x += 120; break;
	default:addDistance.x += 180; break;
	}
	targetPos = position + (addDistance*(float)_direction);

	rotateComponent->SetRotation(90, Vector3::UnitY);

	if (_direction == 1)
	{
		rotateComponent->SetRotation(180, Vector3::UnitX);
	}
}

WeaponRotationAnimationPlayer::~WeaponRotationAnimationPlayer()
{
}

void WeaponRotationAnimationPlayer::UpdateWeaponGameObject(float _deltaTime)
{
	Rotate();
	Vector3 add = Vector3((targetPos.x - position.x) * 0.05f, 0, 0);
	SetPosition(position + add);
}

void WeaponRotationAnimationPlayer::Rotate()
{
	if (rotateSpeed >= 0)
	{
		rotateComponent->SetRotation(rotateSpeed*-direction, Vector3::UnitZ);
		if (rotateSpeed < 3)
		{
			rotateSpeedSub = 0.1f;
		}
		rotateSpeed -= rotateSpeedSub;
	}
}
