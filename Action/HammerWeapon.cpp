#include "HammerWeapon.h"
#include "RotateComponent.h"

/*
@param _pos ���W
@param _number �R���{��
@param _direction ����
@param _lifeCount ��������
@param _waitTime�@�ҋ@����
*/
HammerWeapon::HammerWeapon(const Vector3 & _pos, const float & number, const float & _direction, const int& _lifeCount, const int & _waitTime)
	:WeaponBase(_pos, _waitTime, _lifeCount, _direction,
		Tag::PlayerWeaponTag,4, Vector3(160, 100, 100),0.08f, "Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpmesh", "Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpskel")
{
	SetPosition(_pos + Vector3(((30.0f * number)*_direction), 0, 0));

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
@fn �������Ԃ����ȏ�ɂȂ�Ɖ�]���x��ύX����
*/
void HammerWeapon::UpdateWeaponGameObject(float _deltaTime)
{
	rotateComponent->SetRotation(rotateSpeed, Vector3::UnitZ);
	if (activeCount == 15)
	{
		doCollision = true;
		rotateSpeed *= 49.0f;
	}
	if (activeCount == 19)
	{
		rotateSpeed /= 35.0f;
	}
}
