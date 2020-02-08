#pragma once
#include "WeaponBase.h"

/*
 @file ThrowWeapon.h
 @brief ���������Ɩ�̂悤�ɔ��ł����v���C���[�̍U��
	*/
class ThrowWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos ����������W
	@param _direction �������ꂽ�ۂ̃v���C���[�̌���
	*/
	ThrowWeapon(const Vector3& _pos, const float& _direction,const int& _waitTime, const Tag& _tag=Tag::PlayerWeaponTag);
	~ThrowWeapon();
private:
	void UpdateWeaponGameObject(float _deltaTime);
	void OnTriggerStay(ColliderComponent* _collider)override;
	//�ړ���
	Vector3 velocity;
	//�Փ˂�����
	bool collided;
	//���Ă��ォ�B���Ă����Ă���d�͂�����
	bool slow;
};

