#pragma once
#include "Component.h"

/*
	 @enum PlayerAttackState
	 Player�̋ߐڃR���{�̏��
*/
enum PlayerAttackState
{
	NoAttack,
	AttackOnce,
	AttackTwice,
	AttackThird,
	EndAttack,
};

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
	@brief ���͂��ꂽ�ۂ̍U�����s���A���̍U���̏���������
	@param _direction �U�����̃v���C���[�̌���
	@return �v���C���[�ɕt�^����s���s�Ȏ���
	*/
	float Attack(int _direction);
	/*
	@fn �������U��
	@brief ���͂��ꂽ�ۂ̍U�����s���A���̍U���̏���������
	@param _direction �U�����̃v���C���[�̌���
	@return �v���C���[�ɕt�^����s���s�Ȏ���
	*/
	float RangeAttack(int _direction);
private:
	//�ߋ����U���̏��
	PlayerAttackState attackState;
	//�������U���̉�
	int rangeAttackCount;
	//�U�����s���N���X�ւ̃A�h���X
	class AttackBase* attack;
	//�ߋ����U���̃R���{�����ɂȂ���P�\���ԁB���ꂪ0�ɂȂ�ƃR���{��Ԃ����Z�b�g����
	float waitTimeForNextAttack;
};

