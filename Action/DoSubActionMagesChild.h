#pragma once
#include "GameObject.h"

/*
 @file DoSubActionMagesChild.h
 @brief �e�I�u�W�F�N�g�̈ړ���e�N���X����̗v���ɍ��킹�s�� MageEnemy�N���X�ɂĎg�p
 @detail �n�ʂ֐ڐG����܂ŗ����A���̍����܂ŕ���A���E�̕ǂɓ�����܂ō��E�ړ�������
	*/
class DoSubActionMagesChild :
	public GameObject
{
public:
	/*
	@param _owner �e�ƂȂ�I�u�W�F�N�g�N���X
	*/
	DoSubActionMagesChild(GameObject* _owner);
	~DoSubActionMagesChild();

	/*
	@fn �ǂ̍s�����s�������f���A�s��
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn ���̃N���X���̒萔���̍����܂ŕ��シ��
	*/
	void StartFloating();
	/*
	@fn �T�u�N���X���n�ʂ����m����܂ŗ�������
	@sa SkeltonObjectChecker.h
	*/
	void StartDroppingDown();
private:
	//�e�I�u�W�F�N�g�ւ̃|�C���^
	GameObject* owner;
	//���シ�鍂��
	static const float FloatHeight;
	//����̖ڕW�ƂȂ鍂�� FloatHeight+�e�I�u�W�F�N�g�̍���
	float targetHeight;
	//���㑬�x
	static const float FloatSpeed;
	//����̖��߂��e�I�u�W�F�N�g���痈�Ă����� droppingDown�Ɠ����Ɍ����Ƃ͂Ȃ�
	bool floating;
	
	//�n�ʂ����m����N���X
	class SkeltonObjectChecker* footChcker;
	//�����̖��߂��e�I�u�W�F�N�g���痈�Ă����� floating�Ɠ����Ɍ����Ƃ͂Ȃ�
	bool droppingDown;
	//�������x
	static const float DroppingSpeed;
};

