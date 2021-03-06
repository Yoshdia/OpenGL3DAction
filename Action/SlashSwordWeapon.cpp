#include "SlashSwordWeapon.h"
#include "RotateComponent.h"

/*
@param _pos 座標
@param _stage 段階
@param _direction 向き
@param _lifeCount 生存時間
@param _waitTime 待機時間
*/
SlashSwordWeapon::SlashSwordWeapon(const Vector3& _pos, const float& _stage, const float& _direction, const int& _lifeCount, const int& _waitTime):
	WeaponBase(_pos, _waitTime, _lifeCount, _direction,
		Tag::PlayerWeaponTag, 2, Vector3(160, 100, 100), 0.04f, "Assets/Model/Weapon/SK_Blade_BlackKnight.gpmesh", "Assets/Model/Weapon/SK_Blade_BlackKnight.gpskel"),
	rotateSpeed(8.0f)
{
	Vector3 addDistance = Vector3(0, 0, 0);
	rotateDirection = 1;
	int stage = (int)_stage;
	switch (stage)
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

/*
@fn 活動時間が一定以上になると回転速度を変更する
*/
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
