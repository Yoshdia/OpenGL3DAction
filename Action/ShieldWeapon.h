#pragma once
#include "GameObject.h"
#include <functional>

/*
 @file ShieldWeapon.h
 @brief �v���C���[���琶������鏂
	*/
class ShieldWeapon :
	public GameObject
{
public:
	/*
	param _AddGuardingObjectIdFunc ���̃I�u�W�F�N�g�ƐڐG�����I�u�W�F�N�gID��n����̊֐��|�C���^
	*/
	ShieldWeapon(std::function<void(const int&)> _AddGuardingObjectIdFunc);
	~ShieldWeapon();
	/*
	@brief �������ꂽ�ۂ̉��o�A�A�N�e�B�u���Ԃ̊Ǘ�
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn ����
	@brief �e�J�E���g����W�����Z�b�g����
	@param ����������W ���̍��W���班���������W�ɐ������ꂱ�̍��W�ɗ�������
	*/
	void CreateShield(const Vector3& _pos);
private:
	/*
	@brief �R���X�g���N�^����󂯎�����֐��ɏՓ˂����I�u�W�F�N�g��ID��n��
	*/
	void OnTriggerStay(ColliderComponent* _colliderPair)override;
	//�R���X�g���N�^����󂯎�����֐�
	std::function<void(const int&)> AddGuardingObjectIdFunc;
	//�A�N�e�B�u����
	int activeCount;
	//�A�N�e�B�u���Ԃ̍ő吔
	static const int ActiveCount;

	//��������鍂�� �������̃v���C���[�̍����ɑ���
	static const float CreatedHeightShield;
	//������Ɍ����������@�������̃v���C���[�̍���
	int targetHeight;
	//���V���� 0�ɂȂ�Ɨ�������
	int floatingCount;
	//���V���Ԃ̍ő吔
	static const int FloatingCount;
};

