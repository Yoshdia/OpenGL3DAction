#pragma once
#include "EventSystem.h"

/*
 @file SpawnEventSystem.h
 @brief ���͈͂Ƀv���C���[���N�������Ƃ��ɓ������ǂ�Mage���A�N�e�B�u�ɂ���
*/
class SpawnEventSystem :
	public EventSystem
{
public:
	/*
	@param _pos ���W
	@param _wallPos �v���C���[���N�����Ă����Ƃ��ɂӂ����ǂ̍��W
	@param _goalPos MageEnemy�����j���ꂽ�Ƃ��ɍ폜����ǂ̍��W
	*/
	SpawnEventSystem(const Vector3& _pos, const Vector3& _wallPos,const Vector3& _goalPos);
	~SpawnEventSystem();
private:
	/*
	@brief �v���C���[�̐N�������m�����Ƃ��Ƀt���O�����Ă�
	*/
	void OnTriggerEnter(ColliderComponent* _pair)override;
	void UpdateEventObject() override ;
	//�A�N�e�B�u�ɂ���Mage�N���X�|�C���^
	class MageEnemy* mageEnemy;
	//�f�o�b�O�p�A�q�b�g�{�b�N�X�̊m�F��
	class MeshComponent* meshComponent;
	//���o�̃X�^�[�g�t���O
	bool startDirecting;
	//�N�������m������ɕǂ𐶐�������W
	Vector3 wallPos;
public://�Q�b�^�[�Z�b�^�[
	/*
	@return MageEnemy�̃|�C���^
	*/
	class MageEnemy* GetMageEnemy() { return mageEnemy; }

};

