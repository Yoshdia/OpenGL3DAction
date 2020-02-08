#include "ShotSwordWeapon.h"
#include "RotateComponent.h"

/*
@param _pos ���W
@param _directipn ����
@param _lifeCount ��������
@param _waitTime �ҋ@����
*/
ShotSwordWeapon::ShotSwordWeapon(const Vector3& _pos, const float& _direction, const int& _lifeCount, const int& _waitTime) :
	WeaponBase(_pos, _waitTime, _lifeCount, _direction,
		Tag::PlayerWeaponTag, 4, Vector3(10, 10, 10), 0.04f, "Assets/Model/Weapon/SK_Blade_BlackKnight.gpmesh", "Assets/Model/Weapon/SK_Blade_BlackKnight.gpskel")
{
	rotateComponent->SetRotation(90 * _direction, Vector3::UnitY);
}

ShotSwordWeapon::~ShotSwordWeapon()
{
}

/*
@fn �������Ԃ����ȏ�ɂȂ�Ɖ�]���x��ύX����
*/
void ShotSwordWeapon::UpdateWeaponGameObject(float _deltaTime)
{
	rotateComponent->SetRotation(20, Vector3::UnitX);

	SetPosition(position + (Vector3(35, 0, 0) * direction));
}
