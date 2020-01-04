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
	void SetAttackState(GameObject* _playerObject);
private:
	void UpdateEnemyObject(float _deltaTime)override;
	GameObject* playerObject;
	void AliveLoiteringEnemyCheck();
	void DeadEvent()override;
	void HitPlayerAttack(const Vector3& _pairPos)override;
	bool attackState;
	int directingCount;
	class LoiteringEnemyBase* meleeEnemy;
	class LoiteringEnemyBase* rangeEnemy;
	Vector3 popLoiteringEnemyPosition;
	bool barrier;
	int stanCount;
	static const int StanCount;
	int chargeCount;
	static const int ChargeCount;
	enum MageActionName
	{
		SkillCharge,
		Skill,
		FloatShot,
		Stanning,
		None
	};
	MageActionName actionName;
	class DoSubActionMagesChild* subActionClass;

	void Shot(const Vector3& target);
	int shotInterval;
	static const int ShotInterval;
};

