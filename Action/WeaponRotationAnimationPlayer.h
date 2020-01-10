#pragma once
#include "WeaponBase.h"

/*
 @file WeaponRotationAnimationPlayer.h
 @brief ��]���Ȃ���O�i���A���ʒu�܂Ői�ނƎ~�܂�v���C���[�̍U��
	*/
class WeaponRotationAnimationPlayer :
	public WeaponBase
{
public:
	/*
	@param _pos ����������W
	@param _moveDistance �ړ��ʁA�͈͂�0~2
	*/
	WeaponRotationAnimationPlayer(const Vector3& _pos, const int& _direction, const int& _waitCount, const int& _lifeCount, const int& _moveDistanceStage);
	~WeaponRotationAnimationPlayer();
private:
	void UpdateWeaponGameObject(float _deltaTime);
	/*
  @fn ��]
  @brief ��]���x�����������炵�Ȃ����]����
*/
	void Rotate();
	//��]���x�B���I�ɕω�
	float rotateSpeed;
	//��]���x�̌������BrotateSpeed�����l�܂Ō���Ɛ����ω�����
	float rotateSpeedSub;
	//�ړ��̖ڕW�ʒu�A��������_moveDistanceStage�����ƂɌ���
	Vector3 targetPos;
};

