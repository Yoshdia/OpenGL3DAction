#pragma once
#include "LoiteringEnemyBase.h"
/*
@file ShieldEnemy.h
@brief ���ʂ���̍U�����u���b�N����G
*/
class ShieldEnemy :
	public LoiteringEnemyBase
{
public:
	/*
@param _pos ���W
*/
	ShieldEnemy(const Vector3& _pos);
	~ShieldEnemy();

private:
	void UpdateLoiteringEnemyObject(float _deltaTime)override;
	void DeadEvent()override;
	void Attack(float _deltaTime)override;

	void HitPlayerAttack(const Vector3& _pairPos, const int& _power)override;

	//�����̗́@�[���ɂȂ�ƌ��j�A�j���[�V�����Ƌ��ɏ�����
	static const int HitPointMax;
	//�U������
	static const float AttackingTime;
	//��e���ԁA��e���ɂ��̒萔��canNotActionTime�ɓ���
	static const float HittingTime;
	//���s���x
	static const float WalkSpeed;
	//�U���Ώۂւ̐ڋߑ��x
	static const float ApproachSpeedRatio;
	//��������͈�
	static const float SearchRange;
	//�U���̎˒�����
	static const float AttackRange;
	//���̍U���܂ł̃C���^�[�o���ő吔
	static const int AttackIntervalCount;
};

