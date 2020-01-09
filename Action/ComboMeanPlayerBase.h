#pragma once
#include "GameObject.h"

#include "AttackBase.h"

/*
 @file ComboMeanPlayerBase.h
 @brief 1,2,3�Ȃǂ̃R���{���s���R���{�N���X�̊��N���X
*/
class ComboMeanPlayerBase
{
public:
	~ComboMeanPlayerBase();
	/*
	@fn AttackPlayerComponent����Ă΂��B�U�����s��
	@param _pos �U�����s�����W
	@param _direction �U�����s������
	@param &_playerCanNotMoveTime �U����v���C���[�̍s���s���ԁA�d������������ϐ��ւ̎Q��
	@param &_waitTimeForNextAttack �U����d�����玟�̍U���܂ł̎��Ԃ���������ϐ��ւ̎Q��
	*/
	void Attack(const Vector3& _pos, const int& _direction, float& _playerCanNotMoveTime, float& _waitTimeForNextAttack);
	/*
	@fn AttackPlayerComponent����Ă΂��B�U����Ԃ����Z�b�g����B
	@detail AttackPlayerComponent���ŊǗ�����Ă���A���̍U���܂ł̎���waitTimeForNextAttack���[���ɂȂ����Ƃ��ɌĂ΂��B
	*/
	void ComboReset() { attackState = AttackState::NoAttack; }
	/*
	@return ���̃R���{���������U�����ǂ����B�v���C���[�̃A�j���[�V�����ɈႢ�����܂��̂Ŏw�肪�K�v
	*/
	bool GetRangeFlag() { return range; }

	virtual void DropMyItem(const Vector3& _pos) {};
protected:
	/*
	@enum �R���{���
	*/
	enum AttackState
	{
		//�U�����s���Ă��Ȃ����
		NoAttack,
		//1�i�ڂ̍U�����I���������
		AttackOnce,
		//2�i�ڂ̍U�����I���������
		AttackTwice,
		//3�i�ڂ̍U�����I���������
		AttackThird,
		//4�i�ڂ̍U�����I���������
		AttackFourth,
		//���ׂĂ̍U�����I���������
		EndAttack,
	};
	/*
	@fn �����R���{���ƍŏI�R���{endAttackState������������,endAttackState�͌p����N���X�Ŏw��
	*/
	ComboMeanPlayerBase(const AttackState& _endAttack, const bool& _range = false);
	//�I���R���{�A3�i�Ȃ�AttackThird
	AttackState endAttackState;
private:
	//�������U�����ǂ����B�v���C���[�̃A�j���[�V�����ɈႢ�����܂��̂Ŏw�肪�K�v
	bool range;
	//���݂̃R���{
	AttackState attackState;
	//�U���N���X�A�X�e�[�g�p�^�[����p���Đ؂�ւ���
	class AttackBase* attack;
	/*
	@fn �p����N���X�Ŏw��A���ʎq_attackState�����ƂɍU������
	@param _attackState ���݂̃R���{��n��
	@return �U���N���X
	*/
	virtual AttackBase* GetComboAttack(const AttackState& _attackState);
};
