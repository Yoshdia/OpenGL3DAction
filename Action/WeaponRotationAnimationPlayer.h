#pragma once
#include "GameObject.h"

/*
 @file WeaponRotationAnimationPlayer.h
 @brief ��]���Ȃ���O�i���A���ʒu�܂Ői�ނƎ~�܂�v���C���[�̍U��
	*/
class WeaponRotationAnimationPlayer :
	public GameObject
{
public:
	/*
	@param _pos ����������W
	@param _moveDistance �ړ��ʁA�͈͂�0~2
	*/
	WeaponRotationAnimationPlayer(const Vector3& _pos, const int& _direction, const int& _moveDistanceStage);
	~WeaponRotationAnimationPlayer();
	void UpdateGameObject(float _deltaTime);
private:
	class MeshComponent* meshComponent;
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
	int direction;
	class RotateComponent* rotateComponent;
};

