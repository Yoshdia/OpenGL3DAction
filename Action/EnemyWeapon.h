#pragma once
#include "GameObject.h"

/*
@file EnemyWeapon.h
@brief �G�l�~�[�̍U���B��{�I�ɃA�j���[�V�����Ƌ��ɐ������U������ɂ���B�q�b�g�{�b�N�X��z��
*/
class EnemyWeapon :
	public GameObject
{
public:
	/*
	@param _pos ���W
	@param _size �T�C�Y
	@param _lifeCount ���莞��
	@param _waitTime �U�������܂őҋ@����
	*/
	EnemyWeapon(Vector3 _pos,Vector3 _size,int _lifeCount,int _waitTime);
	~EnemyWeapon();

	/*
	@fn �������Ԃ��������������[���ɂȂ��������̃I�u�W�F�N�g�̍X�V���~�߂�
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	//��������
	int lifeCount;
	//�ҋ@����
	int waitTime;
	//�f�o�b�O�p�B�q�b�g�{�b�N�X�̊m�F��
	class MeshComponent* meshComponent;
	//�Փ˔�����s���N���X
	class ColliderComponent* collisionComp;
};

