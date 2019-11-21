#pragma once
#include "Component.h"
#include <vector>

class ShieldWeapon;

/*
 @file GuardPlayerComponent.h
 @brief ���𐶐����A���ƐڐG�����G�����id���L������
*/
class GuardPlayerComponent :
	public Component
{
public:
	GuardPlayerComponent(GameObject* owner, int updateOrder);
	~GuardPlayerComponent();

	/*
	@fn �h�䒆�̃I�u�W�F�N�g�̒����猟������
	@param _id �����������I�u�W�F�N�g
	@return �������� ������...true
	*/
	bool SearchObjectId(const int& _id);
	/*
	@fn �h��A�N�V����
	@brief ���̏��������s��
	@return �A�N�V�����̍d������
	*/
	float Guard();
	/*
	@brief ������A�N�e�B�u��ԂłȂ����𒲂ׁA�����������Ƃ��h�䃊�X�g�����Z�b�g����
	*/
	void Update(float _deltaTime)override;
private:
	//�v���C���[�ɕt�^����A�N�V�����d������
	static const float canNotActionTime;
	//�h�䒆�I�u�W�F�N�g��id
	std::vector<int> guardingObjectIds;
	/*
	@fn �h�䂵���I�u�W�F�N�g�̒ǉ�
	@brief ShieldWeapon����Ă΂�A���ɒǉ��ς݂łȂ����𒲂ׂĒǉ�����
	*/
	void AddGuardingObjectId(const int& _id);
	//�J�������猩�ĉE�ɂ��鏂
	ShieldWeapon* rightShield;
	//�J�������猩�č��ɂ��鏂
	ShieldWeapon* leftShield;
	//���E�̏��Ԃ̌���
	static const float ShieldSpace;
};

