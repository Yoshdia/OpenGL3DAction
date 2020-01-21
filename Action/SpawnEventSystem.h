#pragma once
#include "EventSystem.h"

/*
 @file SpawnEventSystem.h
 @brief ���͈͂Ƀv���C���[���N�������Ƃ��ɏo�����ǂ�Mage���A�N�e�B�u�ɂ���
*/
class SpawnEventSystem :
	public EventSystem
{
public:
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

	class MeshComponent* meshComponent;
	//���o�̃X�^�[�g�t���O
	bool startDirecting;
	//�N�������m������ɕǂ𐶐�������W
	Vector3 wallPos;
};

