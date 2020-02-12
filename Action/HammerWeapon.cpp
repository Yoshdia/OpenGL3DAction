#include "HammerWeapon.h"
#include "RotateComponent.h"

/*
@param _pos 座標
@param _number コンボ回数
@param _direction 向き
@param _lifeCount 生存時間
@param _waitTime　待機時間
*/
HammerWeapon::HammerWeapon(const Vector3& _pos, const float& number, const float& _direction, const int& _lifeCount, const int& _waitTime)
	:WeaponBase(_pos, _waitTime, _lifeCount, _direction,
		Tag::PlayerWeaponTag, 3, Vector3(160, 100, 100), 0.08f, "Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpmesh", "Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpskel")
{
	Vector3 hammerPos = Vector3(30.0f * number, 0, 0);
	if (number != 1)
	{
		hammerPos.x = 60.0f;
	}
	SetPosition(_pos + (hammerPos * _direction));

	if (_direction == 1)
	{
		rotateComponent->SetRotation(90, Vector3::UnitY);
		rotateComponent->SetRotation(150, Vector3::UnitZ);
		rotateSpeed = -1.0f;
	}
	else
	{
		rotateComponent->SetRotation(-90, Vector3::UnitY);
		rotateComponent->SetRotation(-150, Vector3::UnitZ);
		rotateSpeed = 1.0f;
	}
	rotateComponent->SetRotation(90, Vector3::UnitX);
	doCollision = false;
}

HammerWeapon::~HammerWeapon()
{
}

/*
@fn 活動時間が一定以上になると回転速度を変更する
*/
void HammerWeapon::UpdateWeaponGameObject(float _deltaTime)
{
	rotateComponent->SetRotation(rotateSpeed, Vector3::UnitZ);
	if (activeCount < 15)
	{
		doCollision = false;
	}
	if (activeCount == 15)
	{
		rotateSpeed *= 49.0f;
		doCollision = true;
	}
	else if (activeCount == 19)
	{
		rotateSpeed /= 35.0f;
	}
	else if (activeCount == 30)
	{
	}
}
