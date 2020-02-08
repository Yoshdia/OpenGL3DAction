#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>

/*
@file WeaponBase.h
@brief �v���C���[�̕�����N���X�B��������͔����A���̐F�ɖ߂��Ă���
*/
class WeaponBase :
	public GameObject
{
public:
	/*
	@param _pos ���W
	@param _waitCount �ҋ@����
	@param _lifeCount ��������
	@param _direction ����
	@param _tag �^�O
	@param _weaponName ����̈З�
	@param _colliderSize �Փ˔͈�
	@param _colorSub �����F���猳�̐F�ɖ߂�܂ł̑��x
	@param _meshFileName ���b�V���f�[�^�̃A�h���X
	@param _skeletalFileName �X�P���g���f�[�^�̃A�h���X
	*/
	WeaponBase(const Vector3& _pos, const int& _waitCount, const int& _lifeCount, const float& _direction, const Tag& _tag,const int& _weaponName, const Vector3& _colliderSize,const float& _colorSub, const std::string & _meshFileName, const char * _skeletalFileName);
	~WeaponBase();
	/*
	@fn ���̐F�ɖ߂�
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn �I�u�W�F�N�gID����ɈЗ͂���������
	@param _objectId �I�u�W�F�N�gID
	@return �З�
	*/
	static int SearchWeaponPower(const int& _objectId);
protected:
	//��]��⏕����N���X
	class RotateComponent* rotateComponent;
	//����
	int direction;
	//��������
	int activeCount;
	/*
	@fn �h���N���X���Ƃ̍X�V�֐�
	*/
	virtual void UpdateWeaponGameObject(float _deltaTime) {};
	//�Փ˂��s����
	bool doCollision;
private:
	//�I�u�W�F�N�gID���Ƃ̈З͂��L��
	static std::unordered_map<int,int> weapons;
	//�Փ˔���N���X
	class ColliderComponent* colliderComponent;
	//�X�P���g���N���X
	class SkeletalMeshComponent* skeletalComponent;
	//�ҋ@����
	int waitCount;
	//��������
	int lifeCount;
	//���݂̐F
	float color ;
	//�F�̌����l
	float colorSub;
};

