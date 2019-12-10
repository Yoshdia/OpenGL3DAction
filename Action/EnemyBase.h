#pragma once
#include "GameObject.h"
#include <string>

class SkeltonObjectChecker;

/*
	 @enum EnemyMoveDirection
	 Enemy���ړ��������
*/
enum EnemyMoveDirection
{
	right = 1,
	left = -1,
};

/*
	 @enum EnemyActions
	 Enemy�̋��ʃA�N�V����
*/
enum EnemyActions
{
	//���s
	walk,
	//�_����
	noActive,
	//�U���Ώۂ𔭌����ڋߒ�
	approach,
	//�U����
	attack,
};

/*
 @file EnemyBase.h
 @brief �G�̊��N���X �G���ƂɌ��肷��ϐ�(�̗͂Ȃ�)�͍ŉ����Ő錾
	*/
class EnemyBase abstract :
	public GameObject
{
public:
	/*
	@param meshName mesh��
	*/
	EnemyBase(Vector3 _pos,const std::string& meshName);
	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;
protected:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;

	//���̃J�E���g��0�ȉ��łȂ��ƍs�����ł��Ȃ��B�U�������e���ɃJ�E���g��������
	int canNotActionTime;

	//�����t���O
	bool isLive;
	/*
	@fn ���S���̃C�x���g
	*/
	virtual void DeadEvent() {};

	//�A�j���[�V�������Ǘ�����N���X
	class AnimationEnemyComponent* animComponent;

	/*
	@fn �G�l�~�[�ŗL��Update�֐��A�p����Ŏ���
	*/
	virtual void UpdateEnemyObject(float _deltaTime) {};

	//�i�s����
	EnemyMoveDirection moveDirection;
	//�ړ������̔��]�f�B���C�J�E���g�A�s���R�ȋ����𐧌�����
	int turnWaitCount;
	//�ړ������̔��]�f�B���C�J�E���g�̍ő吔
	static const int TurnWaitCountMax;
	//�����̍��W
	static const Vector3 footPos;
	//�����ɒn�ʂ����邩
	SkeltonObjectChecker* footChecker;
	//�G�l�~�[�ɓ����d�̗͂�
	static const float Gravity;

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

	/*
	  @fn �m�b�N�o�b�N
	*/
	void NockBack(float _deltaTime);
	//��e�����ۂ̃m�b�N�o�b�N����
	static const float NockBackPower;
	//�m�b�N�o�b�N�̕����A��
	Vector3 nockBackForce;

	//��萔�܂ōs���ƃA�N�V�������ύX�����J�E��
	int actionChangeCount;
	//�A�N�V�������ύX�����J�E���g�̍ő吔�BActionChangeCountMax+�����Ō���
	int actionChangeCountMax;
	//actionChangeCountMax�̏����l
	static const int ActionChangeCountMax;

	//���s���̃A�N�V����
	EnemyActions actionName;
	/*
	@fn �A�N�V�����ύX
	*/
	void ActionChange();
	/*
	@fn�A�N�V�������Ƃ̏���
	*/
	void Action(float _deltaTime);
	/*
	@fn ���s�A�N�V�������ύX�����֐�
	*/
	void BranchActionChange();
	/*
	@fn actionChangeCountMax�̕ύX���s���֐�
	*/
	void ShuffleCountMax();

	//�U���Ώۂ𔭌�������ǐՂ���͈́B���͈̔͂���Ώۂ��o��ƒǐՂ��~�ߕ��s/�_�������[�h�ɕς��
	SkeltonObjectChecker* trackingRange;
	static const Vector3 TrackingRange;
	//�U���Ԑ����ǂ����Bfalse=���s/�_�����̔�퓬���
	bool attackingState;
	//�e���|�[�g�܂ł̎���
	int teleportChargingTime;
	//���̍U���܂ł̃C���^�[�o��
	int attackIntervalCount;

	//�U���Ԑ� �ǐ�/�U��
	void Attacking(float _deltaTime);
	virtual void Attack(float _deltaTime) {};
	//��U���Ԑ� ���s/�_����
	void NoAttacking(float _deltaTime);

	/**
	~ �ȉ��p����ŕύX���\ ~(�ϐ��̌�ɂ���萔�͎w�肪�Ȃ������ꍇ�̂���) 
	**/
	//�����̗́@�[���ɂȂ�ƌ��j�A�j���[�V�����Ƌ��ɏ�����
	int hitPoint;
	static const int HitPointMax;
	//�U������
	float attackingTime;
	static const float AttackingTime;
	//��e���ԁA��e���ɂ��̒萔��canNotActionTime�ɓ���
	float hittingTime;
	static const float HittingTime;
	//���s���x
	float walkSpeed;
	static const float WalkSpeed;
	//�U���Ώۂւ̐ڋߑ��x
	float approachSpeedRatio;
	static const float ApproachSpeedRatio;
	//��������͈�
	 float searchRange;
	static const float SearchRange;
	//�U���̎˒�����
	float attackRange;
	static const float AttackRange;
	//���̍U���܂ł̃C���^�[�o���ő吔
	int attackIntervalCountMax;
	static const int AttackIntervalCount;
};



