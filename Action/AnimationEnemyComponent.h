#pragma once
#include "BoneAnimationBaseComponent.h"

class Animation;

/*
@enum EnemyType
@brief �G�̎��
*/
enum EnemyType
{
	//�ߐڍU�����s���G
	MeleeType,
	//�������U�����s���G
	RangeType,
	//�̗͂������G
	TankType,
	//�{�X
	MageType,
	//�������������G
	ShieldType
};

/*
 @file AnimationEnemyComponent.h
 @brief ��{�I�ȓG�S�ĂɑΉ�����A���b�V���f�[�^���������A�j���[�V�����̍Đ��֌W�̏������s���N���X
 �C������]�n�A��
*/
class AnimationEnemyComponent :
	public BoneAnimationBaseComponent
{
public:
	/*
	@fn�@�A�j���[�V�����⃂�f�������[�h����
	@param _type �G�̎�ށ@���[�h���郂�f���⃍�[�h����A�j���[�V�������ς��
	*/
	AnimationEnemyComponent(GameObject * _owner, EnemyType _type, int updateOrder = 100);
	~AnimationEnemyComponent();

	/*
	@fn �S�ẴA�j���[�V�����t���O��|��
	*/
	void AllFlagReset();
	/*
     @fn animationName�Ɗe�t���O���Q�Ƃ��ǂ̃A�j���[�V�������Đ����邩�����肵�Đ�����
	*/
	void UpdateAnimationComponent(float _deltaTime)override;
private:

	//�ړ�
	const Animation* moveAnim;
	//�ҋ@
	const Animation* idleAnim;
	//�U��
	const Animation* attackAnim;
	//����
	const Animation* spawnAnim;
	//�X�^��
	const Animation* stanAnim;
	//�A�N�V����
	const Animation* actionAnim;

	/*
	@enum EnemyAnimationName 
	@brief �G�l�~�[�̋��ʃA�N�V������
	*/
	enum EnemyAnimationName
	{
		//�ړ�
		Move,
		//�ҋ@
		Idle,
		//�U��
		Attack,
		//����
		Spawn,
		//�X�^��
		Stan,
		//�A�N�V����
		Action,
	};
	//���݂̃A�j���[�V������
	EnemyAnimationName animationName;

	//�ړ�
	bool move;
	//�U��
	bool attack;
	//����
	bool spawn;
	//�X�^��
	bool stan;
	//�A�N�V����
	bool action;

	//�A�j���[�V�����̌��Đ�����
	float animDuration;
	//�A�j���[�V�����̌�����
	float subAnimDuration;
	//�A�N�V�����A�j���[�V�����̌����ʁB�G�ɂ���Č����ʂ��ς�邽�ߕϐ��ŊǗ�
	float actionAnimationSpeed;
public:	//�Q�b�^�[�Z�b�^�[
	/*
	@return �A�j���[�V�����̎c�莞��
	*/
	float GetAnimDuration() { return animDuration; }
	/*
	@fn �A�j���[�V�����t���O���Z�b�g
	*/
	void SetMove(bool _move) { move = _move; };
	/*
	@fn �A�j���[�V�����t���O���Z�b�g
	*/
	void SetAttack(bool _attack) { attack = _attack; }
	/*
	@fn �A�j���[�V�����t���O���Z�b�g
	*/
	void SetSpawn(bool _spawn) { spawn = _spawn; }
	/*
	@fn �A�j���[�V�����t���O���Z�b�g
	*/
	void SetStan(bool _stan) { stan = _stan; }
	/*
	@fn �A�j���[�V�����t���O���Z�b�g���A�N�V�����A�j���[�V�������Đ�
	*/
	void SetAction(bool _action);
	/*
	@fn �A�j���[�V�����t���O���Z�b�g
	*/
	void SetSubDuration(float _sub) { subAnimDuration = _sub; }
};

