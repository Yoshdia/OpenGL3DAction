#pragma once
#include "EnemyBase.h"

class SkeltonObjectChecker;

/*
@file LoiteringEnemyBase.h
@brief �p�j����G�B�v���C���[�𔭌����U�������Ԃ�v���C���[��T���������Ԃ����B
*/
class LoiteringEnemyBase :
	public EnemyBase
{
public:
	/*
	@param _pos ���W
	@param _scale �T�C�Y
	@param _type �G�l�~�[�̎��
	@sa�@�����͂��ׂ�EnemyBase�ɓn��
	*/
	LoiteringEnemyBase(Vector3 _pos = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1),  EnemyType _type=EnemyType::MeleeType);
	~LoiteringEnemyBase();
	/*
	@fn ���̃I�u�W�F�N�g���g���܂킵�����Ƃ��ɌĂ΂�A�p�����[�^������������
	@param _pos ���W
	@param _hitPoint �̗�
	@brief ���MageEnemy�ɏ��������悤�Ɏg�p�����
	@sa MageEnemy.h
	*/
	void SpawnSummoned(const Vector3& _pos, const int& _hitPoint);
private:
	/*
	@fn �v���C���[�ɍU�����ꂽ
	@brief �̗͂����炵�A��U���Ԑ��������ꍇ�U���Ԑ��Ɉڍs�A�m�b�N�o�b�N����e���̓A�N�V�����o���Ȃ��Ȃ�
	@param _pairPos �Փˑ���̍��W
	@param _power �_���[�W
	*/
	void HitPlayerAttack(const Vector3& _pairPos,const int& _power)override;
	/*
	@fn ���j�C�x���g
	*/
	void DeadEvent()override;
	/*
	@fn ���̜p�j�G�l�~�[���ʂ̍X�V�֐�
	*/
	void UpdateEnemyObject(float _deltaTime)override;
	/*
	@fn �h���N���X�̍X�V�֐�
	*/
	virtual void UpdateLoiteringEnemyObject(float _deltaTime);
	/*
	@fn 2020/02/08���_�ŕK�v����
	*/
	void PausingUpdateGameObject();

	//�����̍��W
	static const Vector3 footPos;
	//�����ɒn�ʂ����邩
	SkeltonObjectChecker* footChecker;
	//�G�l�~�[�ɓ����d�̗͂�
	static const float Gravity;
	   
	/*
	@fn �A�N�V�����ύX
	*/
	void ActionChange();
	//��萔�܂ōs���ƃA�N�V�������ύX�����J�E���g
	int actionChangeCount;
	//�A�N�V�������ύX�����J�E���g�̍ő吔�BActionChangeCountMax+�����Ō���
	int actionChangeCountMax;
	//actionChangeCountMax�̏����l
	static const int ActionChangeCountMax;
	/*
	@fn�A�N�V�������Ƃ̏���
	*/
	void Action(float _deltaTime);
	/*
	@fn ���s���A�N�V�������ύX�����֐�
	*/
	void BranchActionChange();

	/*
	@fn �U���Ԑ��̏���
	*/
	void Attacking(float _deltaTime);
	/*
	@fn �U�����s���֐�
	@sa EnemyWeapon.h
	*/
	virtual void Attack(float _deltaTime);
	/*
	@fn ��U���Ԑ�
	*/
	void NoAttacking(float _deltaTime);

	//�v���C���[�����ꂷ�����ꍇ�Ƀ��[�v���邽�߂Ƀ��[�v�n�_���w�肷��N���X
	class WarpPointSearchEnemy* warpSearch;
	//���[�v�n�_�w�蒆���ǂ���
	bool warpPositonSearching;

	//�ړ������̔��]�f�B���C�J�E���g�A�s���R�ȋ����𐧌�����
	int turnWaitCount;
	//�ړ������̔��]�f�B���C�J�E���g�̍ő吔
	static const int TurnWaitCountMax;

	//�i�s�����̑����ɒn�ʂ����邩
	SkeltonObjectChecker* forwardDownGroundCheck;
	//forwardDownGroundCheck,forwardGroundCheck��X���W
	static const float GroundCheckPos;

	//forwardDownGroundCheck��Y���W
	static const float ForwardDownY;
	//�i�s�����ɕǂ����邩
	SkeltonObjectChecker* forwardGroundCheck;

	//�U���Ώۂ𔭌�����͈�
	SkeltonObjectChecker* findingPlayerCheck;

	//�U���Ώۂ𔭌�������ǐՂ���͈́B���͈̔͂���Ώۂ��o��ƒǐՂ��~�ߕ��s/�_�������[�h�ɕς��
	SkeltonObjectChecker* trackingRange;
	static const Vector3 TrackingRange;

	//�e���|�[�g�܂ł̎���
	int teleportChargingTime;


	/*
	@fn �m�b�N�o�b�N
	*/
	void NockBack(float _deltaTime);
	//��e�����ۂ̃m�b�N�o�b�N����
	static const float NockBackPower;
	//�m�b�N�o�b�N�̕����A��
	Vector3 nockBackForce;
	//�̗͂̍ő�l
	static const int HitPointMax;
	//�U������
	static const int AttackingTime;
	//��e���̍d��
	static const int HittingTime;
	//���s���x
	static const float WalkSpeed;
	//�ǐՑ��x
	static const float ApproachSpeedRatio;
	//���G�͈�
	static const float SearchRange;
	//�U���J�n����
	static const float AttackRange;
	//�U���̑ҋ@����
	static const int AttackIntervalCount;
protected:

	//���̃J�E���g��0�ȉ��łȂ��ƍs�����ł��Ȃ��B�U�������e���ɃJ�E���g��������
	int canNotActionTime;
	/*
	@fn �������֐�
	@brief �h���N���X���ƂɕύX���s��ꂽ�萔��ʃN���X�ɔ��f�����邽�߂ɕʌɗp��
	*/
	void InstantiateLoiteringEnemyBase();

	//�U���Ԑ����ǂ����Bfalse=���s/�_�����̔�퓬���
	bool attackingState;
	//���s���̃A�N�V����
	EnemyActions actionName;

	//�U������
	int attackingTime;
	//��e���ԁA��e���ɂ��̒萔��canNotActionTime�ɓ���
	int hittingTime;
	//���s���x
	float walkSpeed;
	//�U���Ώۂւ̐ڋߑ��x
	float approachSpeedRatio;
	//��������͈�
	float searchRange;
	//�U���̎˒�����
	float attackRange;
	//���̍U���܂ł̃C���^�[�o���ő吔
	int attackIntervalCountMax;
	//���̍U���܂ł̃C���^�[�o��
	int attackIntervalCount;
};

