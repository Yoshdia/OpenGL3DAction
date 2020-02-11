#pragma once
#include "EnemyBase.h"

/*
@file MageEnemy.h
@brief �{�X
*/
class MageEnemy :
	public EnemyBase
{
public:
	/*
	@param _pos ���W
	*/
	MageEnemy(Vector3 _pos);
	~MageEnemy();
	/*
	@brief �Q�[���I�u�W�F�N�g��~���ɍX�V�A���g�ɃJ�����������A�j���[�V�������Đ��A�G����PoP������
	*/
	void PausingUpdateGameObject()override;
private:
	/*
	@fn ���(MageActionName)���Ƃ̃A�N�V�������s��
	*/
	void UpdateEnemyObject(float _deltaTime)override;

	/*
	@fn �A�N�V�������s���ΏۂɂȂ�I�u�W�F�N�g�B�v���C���[
	*/
	GameObject* playerObject;
	/*
	@fn ���������G���������Ă��邩�B���Ă��Ȃ��Ƃ��X�^������B
	*/
	void AliveLoiteringEnemyCheck();
	/*
	@fn ���j�C�x���g
	*/
	void DeadEvent()override;
	/*
	@fn �U�����ꂽ�Ƃ��B���������G���������Ă���Ƃ��U��������Ȃ�
	*/
	void HitPlayerAttack(const Vector3& _pairPos,const int& _power)override;
	//�v���C���[���U���͈͂ɓ����Ă��邩�B
	bool attackState;
	//���o���ɑ���������J�E���g ������Q�Ƃ��ăJ�����̈ړ��ʒu�����߂��肷��B
	int directingCount;
	//��������ߐڃG�l�~�[�N���X
	class LoiteringEnemyBase* meleeEnemy;
	//�������鉓�����G�l�~�[�N���X
	class LoiteringEnemyBase* rangeEnemy;
	//��������G�l�~�[�̍��W
	Vector3 popLoiteringEnemyPosition;
	//���������G���������Ă���Ƃ��U��������Ȃ��悤�ɂ��邽�߂̃t���O
	bool barrier;
	//�X�^���J�E���g
	int stanCount;
	//�X�^���J�E���g�̍ő吔
	static const int StanCount;
	//�U���̑ҋ@�J�E���g
	int chargeCount;
	//�U���̑ҋ@�J�E���g�ő吔
	static const int ChargeCount;
	/*
	@enum MageActionName
	����MageEnemy�̃A�N�V������
	*/
	enum MageActionName
	{
		//�X�^��>�����̑ҋ@����
		SkillCharge,
		//������
		Skill,
		//���V���v���C���[�ɒe�𔭎˂��Ă���
		FloatShot,
		//�X�^��
		Stanning,
		//�������Ă��Ȃ� ��U���Ԑ�
		None
	};
	//���s���̃A�N�V������
	MageActionName actionName;
	//���V�A�����A���]�Ȃǂ��s���T�u�N���X
	class DoSubActionMagesChild* subActionClass;
	//���̃I�u�W�F�N�g�����j���ꂽ�Ƃ��ɏ����I�u�W�F�N�g�B�S�[���̕�
	GameObject* goalWallObject;
	/*
	@fn �v���C���[�Ɍ����Ēe�𔭎˂���
	@param _target �ڕW���W
	*/
	void Shot(const Vector3& target);
	//�e�̑ҋ@�J�E���g
	int shotInterval;
	//�e�̑ҋ@�J�E���g�ő吔
	static const int ShotInterval;
	//�{�X�Ƀ_���[�W���ʂ�Ȃ����Ƃ��A�s�[�����邽�߂̃V�[���h�摜
	class ParticleObject* guardParticle;
public://�Q�b�^�[�Z�b�^�[
	/*
@brief �ҋ@��Ԃ���퓬��Ԃɓ���֐��@��������
*/
	void SetAttackState(GameObject* _playerObject);

	/*
	@fn�@���̃I�u�W�F�N�g�����j���ꂽ���ɏ����ǁ@�o��
	*/
	void SetGoalWall(GameObject* _wall) { goalWallObject = _wall; }
};

