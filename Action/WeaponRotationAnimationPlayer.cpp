#include "WeaponRotationAnimationPlayer.h"
#include "RotateComponent.h"

/*
@param _pos ¶¬‚·‚éÀ•W
@param _moveDistance ˆÚ“®—ÊA”ÍˆÍ‚Í0~2
*/
WeaponRotationAnimationPlayer::WeaponRotationAnimationPlayer(const Vector3& _pos, const float& _direction, const int& _waitCount, const int& _lifeCount, const int& _moveDistanceStage) :
	WeaponBase(_pos, _waitCount, _lifeCount, _direction,
		Tag::PlayerWeaponTag, 2, Vector3(100, 100, 100), 0.02f, "Assets/Model/Weapon/SK_Blunt_SpikedClub.gpmesh", "Assets/Model/Weapon/SK_Blunt_SpikedClub.gpskel"),
	rotateSpeed(50),
	rotateSpeedSub(0.45f)
{
	SetScale(0.5f);
	Vector3 addPosition = Vector3(0, 0, 0);
	Vector3 addDistance = Vector3(0, 0, 0);
	switch (_moveDistanceStage)
	{
	case(0):
		addPosition.y += 70;
		addDistance.x += 60;
		addDistance.y -= 70;
		break;
	case(1):
		addPosition.y -= 0;
		addDistance.x += 120;
		addDistance.y += 70;
		break;
	default:
		addDistance.x += 200;
		break;
	}

	rotateComponent->SetRotation(90, Vector3::UnitY);

	if (_direction == 1)
	{
		rotateComponent->SetRotation(180, Vector3::UnitX);
	}
	else
	{
		addDistance.x *= -1;
	}
	SetPosition(position + addPosition);
	targetPos = position + (addDistance);
}

WeaponRotationAnimationPlayer::~WeaponRotationAnimationPlayer()
{
}

void WeaponRotationAnimationPlayer::UpdateWeaponGameObject(float _deltaTime)
{
	Rotate();
	Vector3 add = Vector3((targetPos.x - position.x) * 0.05f, (targetPos.y - position.y) * 0.05f, 0);
	SetPosition(position + add);
}

/*
@fn ‰ñ“]
@brief ‰ñ“]‘¬“x‚ð­‚µ‚¸‚ÂŒ¸‚ç‚µ‚È‚ª‚ç‰ñ“]‚·‚é
*/
void WeaponRotationAnimationPlayer::Rotate()
{
	if (rotateSpeed >= 0)
	{
		rotateComponent->SetRotation(rotateSpeed * -direction, Vector3::UnitZ);
		if (rotateSpeed < 3)
		{
			rotateSpeedSub = 0.1f;
			doCollision = false;
		}
		rotateSpeed -= rotateSpeedSub;
	}
}
