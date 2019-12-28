#pragma once
#include "EnemyBase.h"

class SkeltonObjectChecker;


class LoiteringEnemyBase :
	public EnemyBase
{
public:
	LoiteringEnemyBase(Vector3 _pos = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1),  EnemyType _type=EnemyType::MeleeType);
	~LoiteringEnemyBase();

private:
	void HitPlayerAttack(const Vector3& _pairPos)override;
	void DeadEvent()override;
	void UpdateEnemyObject(float _deltaTime)override;
	virtual void UpdateLoiteringEnemyObject(float _deltaTime);

	//�����̍��W
	static const Vector3 footPos;
	//�����ɒn�ʂ����邩
	SkeltonObjectChecker* footChecker;
	//�G�l�~�[�ɓ����d�̗͂�
	static const float Gravity;

	//���̃J�E���g��0�ȉ��łȂ��ƍs�����ł��Ȃ��B�U�������e���ɃJ�E���g��������
	int canNotActionTime;
	//���s���̃A�N�V����
	EnemyActions actionName;
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
	@fn actionChangeCountMax�̕ύX���s���֐�
	*/
	void ShuffleCountMax();

	//�U���Ԑ� �ǐ�/�U��
	void Attacking(float _deltaTime);
	virtual void Attack(float _deltaTime);
	//��U���Ԑ� ���s/�_����
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
	//�U���Ԑ����ǂ����Bfalse=���s/�_�����̔�퓬���
	bool attackingState;
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

	static const int HitPointMax;
	static const float AttackingTime;
	static const float HittingTime;
	static const float WalkSpeed;
	static const float ApproachSpeedRatio;
	static const float SearchRange;
	static const float AttackRange;
	static const int AttackIntervalCount;
protected:
	/*
	@fn �������֐�
	@brief �h���N���X���ƂɕύX���s��ꂽ�萔��ʃN���X�ɔ��f�����邽�߂ɕʌɗp��
	*/
	void InstantiateLoiteringEnemyBase();

	//�U������
	float attackingTime;
	//��e���ԁA��e���ɂ��̒萔��canNotActionTime�ɓ���
	float hittingTime;
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
