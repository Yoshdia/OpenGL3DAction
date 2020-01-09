#pragma once
#include "Component.h"

/*
@file AttackPlayerComponent.h
@brief Player�ɋߐڃR���{�A�������U�����s�킹��N���X
*/
class AttackPlayerComponent :
	public Component
{
public:
	AttackPlayerComponent(GameObject* _owner, int _updateOrder);
	~AttackPlayerComponent();

	void Update(float _deltaTime);

	/*
	@fn �ߋ����U��
	@param _direction �U�����̃v���C���[�̌���
	@param _slot �U���X���b�g
	@param _range ���̃R���{���������U�����ǂ���
	@return �v���C���[�ɕt�^����s���s�Ȏ���
	*/
	float Attack(const int& _direction,const int& _slot,bool& _range);
private:
	//���O�����s���U���X���b�g
	class ComboMeanPlayerBase* firstSlotAttack;
	//���O�����s���U���X���b�g
	class ComboMeanPlayerBase* secondSlotAttack;
	//�ߋ����U���̃R���{�����ɂȂ���P�\���ԁB���ꂪ0�ɂȂ�ƃR���{��Ԃ����Z�b�g����
	float waitTimeForNextAttack;
};

