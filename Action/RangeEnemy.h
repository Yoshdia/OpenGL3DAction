#pragma once
#include "LoiteringEnemyBase.h"
/*
@file RangeEnemy.h
@brief �������U�����s���G
*/
class RangeEnemy :
	public LoiteringEnemyBase
{
public:
	/*
@param _pos ���W
*/
	RangeEnemy(Vector3 _pos);
	~RangeEnemy();

private:
	void UpdateLoiteringEnemyObject(float _deltaTime)override;
	void DeadEvent()override;
	void Attack(float _deltaTime)override;

	//�����̗́@�[���ɂȂ�ƌ��j�A�j���[�V�����Ƌ��ɏ�����
	static const int HitPointMax;
	//�U������
	static const int AttackingTime;
	//��e���ԁA��e���ɂ��̒萔��canNotActionTime�ɓ���
	static const int HittingTime;
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

