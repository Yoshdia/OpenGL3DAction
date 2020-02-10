#pragma once
#include "GameObject.h"
#include <string>
#include "AnimationEnemyComponent.h"


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
	@param _pos ���W
	@param _size �T�C�Y
	@param _enemyType �G�̎�ށ@������Q�Ƃ����b�V���f�[�^��ύX����
	*/
	EnemyBase(Vector3 _pos=Vector3(0,0,0), Vector3 _scale=Vector3(1,1,1), EnemyType _type=EnemyType::MeleeType);

	~EnemyBase();
	/*
	@fn �h���N���X�̍X�V�֐����ĂсA�̗͂��Ǘ��������ɑ΂��ĉ�]���s��
	*/
	void UpdateGameObject(float _deltaTime)override;
protected:
	/*
	@fn �v���C���[�ɍU�����ꂽ�Ƃ��ɁA���b�V���𔭌��������̕���̍U���͂��������h���N���X�̔�e�֐��֓n��
	*/
	void OnTriggerEnter(ColliderComponent* _colliderPair)override;

	//�����̗́@�[���ɂȂ�ƌ��j�p�[�e�B�N���Ƌ��ɏ�����
	int hitPoint;
	//����F�̐i�s����
	EnemyMoveDirection moveDirection;
	//�OF�̐i�s�����A��F�ƈقȂ��Ă����ꍇRotateComponent��p���ĉ�]����
	EnemyMoveDirection beforeDirection;
	//��]���菕������N���X
	class RotateComponent* rotate;
	//�A�j���[�V�������Ǘ�����N���X
	class AnimationEnemyComponent* animComponent;

	/*
	@fn ���S���̃C�x���g
	*/
	void DeadCommonEvent();
	virtual void DeadEvent() {};

	/*
	@fn �G�l�~�[�ŗL��Update�֐��A�p����Ŏ���
	*/
	virtual void UpdateEnemyObject(float _deltaTime) {};
	/*
	@fn ��e���̏����@�m�b�N�o�b�N�Ȃ�
	*/
	virtual void HitPlayerAttack(const Vector3& _pairPos,const int& _power) {};

	/*
	~ �p����ŕύX���s���Ȃ������ꍇ�̍ő�̗� ~
	**/
	static const int HitPointMax;

	//�ł��ŐV�́A�U�����s�����I�u�W�F�N�g�ւ̃|�C���^�B���j���ꂽ�Ƃ��ɍ폜���邽�߂ɏ��L����
	GameObject* attackObject;
	//���S���W
	Vector3 middlePos;
};



/*
~ �R�s�y�p�e���v���[�g ~
**/
//.h�p
/*
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
*/
//.cpp�p
/*
const int LoiteringEnemyBase::HitPointMax = 0;
const float LoiteringEnemyBase::AttackingTime = 0;
const float LoiteringEnemyBase::HittingTime = 0;
const float LoiteringEnemyBase::WalkSpeed = 0;
const float LoiteringEnemyBase::ApproachSpeedRatio = 0;
const float LoiteringEnemyBase::SearchRange = 0;
const float LoiteringEnemyBase::AttackRange = 0;
const int LoiteringEnemyBase::AttackIntervalCount = 0;

hitPoint = HitPointMax;
attackingTime = AttackingTime;
hittingTime = HittingTime;
walkSpeed = WalkSpeed;
approachSpeedRatio = ApproachSpeedRatio;
searchRange = SearchRange;
attackRange = AttackRange;
attackIntervalCount = AttackIntervalCount;

*/