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
 @brief �G�̊��N���X
	*/
class EnemyBase abstract :
	public GameObject
{
public:
	/*
	@param meshName mesh��
	*/
	EnemyBase(const std::string& meshName);
	~EnemyBase();
	void UpdateGameObject(float _deltaTime)override;
protected:
	int canNotActionTime;
	class AnimationEnemyComponent* animComponent;
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;
	/*
	@fn �G�l�~�[�ŗL�̊֐��A�p����Ŏ���
	*/
	virtual void UpdateEnemyObject(float _deltaTime) {};

	//�i�s����
	EnemyMoveDirection moveDirection;
	//�ړ������̔��]�f�B���C�J�E���g�A�s���R�ȋ����𐧌�����
	int turnWaitCount;
	//�ړ������̔��]�f�B���C�J�E���g�̍ő吔
	static const int TurnWaitCountMax;
	//���s���x
	static const float WalkSpeed;
	//�U���Ώۂւ̐ڋߑ��x
	static const float ApproachSpeedRatio;
	//���s���x�̏���l
	static const float WalkSpeedLimit;

	static const Vector3 footPos;
	//�����ɒn�ʂ����邩
	SkeltonObjectChecker* footChecker;
	//�G�l�~�[�ɓ����d�̗͂�
	static const float Gravity;
	//�d�͂̏���l
	static const float GravityLimit;

	//�i�s�����̑����ɒn�ʂ����邩
	SkeltonObjectChecker* forwardDownGroundCheck;
	//forwardDownGroundCheck,forwardGroundCheck��X���W
	static const float GroundCheckPos;

	//forwardDownGroundCheck��Y���W
	static const float ForwardDownY;
	//�i�s�����ɕǂ����邩
	SkeltonObjectChecker* forwardGroundCheck;

	//��������͈�
	static const float SearchRange;
	//�U���Ώۂ𔭌�����͈�
	SkeltonObjectChecker* findingPlayerCheck;
	//�U�����J�n����˒�����
	float attackRange;

	/*
	  @fn �m�b�N�o�b�N
	*/
	void NockBack(float _deltaTime);
	//��e�����ۂ̃m�b�N�o�b�N����
	static const float NockBackPower;
	//�m�b�N�o�b�N�̕����A��
	Vector3 nockBackForce;

	//actionChangeCountMax�̏����l
	static const int DefaultActionChangeCountMax;
	//��萔�܂ōs���ƃA�N�V�������ύX�����J�E���g�Ƃ��̍ő吔
	int actionChangeCount;
	int actionChangeCountMax;
	//�U���Ώۂ𔭌����ĂȂ��Ƃ��A�ړ��Ɩ_������؂�ւ��鎞�Ԃ̋��L�J�E���g
	int defaultActionChangeCountMax;

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
	virtual void BranchActionChange();
	/*
	@fn actionChangeCountMax�̕ύX���s���֐�
	*/
	virtual void ShuffleCountMax();

	//�U���Ώۂ𔭌�������ǐՂ���͈́B���͈̔͂���Ώۂ��o��ƒǐՂ��~�ߕ��s/�_�������[�h�ɕς��
	SkeltonObjectChecker* trackingRange;
	static const Vector3 TrackingRange;
	//�U���Ԑ����ǂ����Bfalse=���s/�_�����̔�퓬���
	bool attackingState;
	//�e���|�[�g�܂ł̎���
	int teleportChargingTime;
	static const float AttackRange;
	int attackIntervalCount;
	static const int AttackIntervalCount;

	//�U���Ԑ� �ǐ�/�U��
	void Attacking(float _deltaTime);
	//��U���Ԑ� ���s/�_����
	void NoAttacking(float _deltaTime);
};



