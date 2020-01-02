#pragma once
#include "EnemyBase.h"

class MageEnemy :
	public EnemyBase
{
public:
	MageEnemy(Vector3 _pos);
	~MageEnemy();
	/*
	@brief �Q�[���I�u�W�F�N�g��~���ɍX�V�A���g�ɃJ�����������A�j���[�V�������Đ��A�G����PoP������
	*/
	void PausingUpdateGameObject()override;
	/*
	@brief �ҋ@��Ԃ���퓬��Ԃɓ���֐��@��������
	*/
	void SetAttackState();
private:
	void UpdateEnemyObject(float _deltaTime)override;
	void AliveLoiteringEnemyCheck();
	void DeadEvent()override;
	void HitPlayerAttack(const Vector3& _pairPos)override;
	bool attackState;
	int directingCount;
	class LoiteringEnemyBase* meleeEnemy;
	bool barrier;
};

