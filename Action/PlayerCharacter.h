#pragma once
#include "GameObject.h"
#include "AnimationPlayerComponent.h"
#include <vector>

struct InputState;


/*
 @file PlayerCharacter.h
 @brief �v���C���[
	*/
class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter(const Vector3& _pos);
	~PlayerCharacter();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState) override;

	void FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag& _pairTag)override;
	void PausingUpdateGameObject();
	bool GetGameOver();
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	//�A�j���[�V����
	class AnimationPlayerComponent* animationComponent;
	//���̗��A��(Ground)��Ώۂɒ��n���Ă��邩�ǂ��������m����
	class SkeltonObjectChecker* footChecker;
	//���̗��A������(ThinGround)��Ώۂɒ��n���Ă��邩�ǂ��������m����
	class SkeltonObjectChecker* thinChecker;

	class SkeltonObjectChecker* headRoofChecker;

	//���͂ɂ��s������������鎞�ԁ@���AttackPlayerComponent�̍U���A�N�V��������󂯎��
	float canNotActionTime;

	//����
	float direction;

	//�ړ���
	Vector3 velocity;

	/*
	@fn �v���C���[���s���A�N�V����
	*/
	void Actions(float _deltaTime,const bool& _noGround);

	//�ߐڃR���{�A�������U�����s���N���X
	class AttackPlayerObject* attack;
	//�ߐڍU���{�^���̓��̓t���O
	bool attackBottonInput;
	//�������U���{�^���̓��̓t���O
	bool rangeAttackBottonInput;

	/*
	@fn �h��
	*/
	//void Guard();
	////�h��̂��߂̏��̐����A�K�[�h�ς݂̍U���̊Ǘ����s���N���X
	//class GuardPlayerComponent* guardComponent;
	////�K�[�h�{�^���̓��̓t���O
	//bool guardBottonInput;
	bool avoidanceBottonInput;
	void Avoidance();
	void AcoidanceIntervalDown();
	bool avoidancing;
	int avoidanceInterval;
	static const int AvoidanceInvincible;
	static const int AvoidanceInterval;
	/*
	@fn ���E�ړ�
	@brief ���E�̓��͏������Ƃ�velocity�֒l�������A�j���[�V�������Đ�����
	*/
	void Move(float _deltaTime);
	//���͕����A��...-1 �E...1
	float inputDirection;
	//�ړ����x
	static const float MoveSpeed;

	/*
	@fn �����������蔲����
	@brief �������ւ̓��͂̒���j���[�g�����ɂ���Ȃǂ̑��삪����܂����̒���ɉ������ւ̓��͂���������t���O�����Ă�(���E��)
	*/
	void SkeletonThinGround();

	//�������ւ̓��͏��A�������̏ォ�炻���ʂ蔲����ۂɎg�p
	float inputUnderDirection;
	//�������ւ̓��͂��s��ꂽ����ɉ������ւ̓��͂������Ȃ����Ƃ��Ɍ��t���O
	bool noInputForUnderDirection;
	//�������̏ォ�炻���ʂ蔲���邽�߂̓��͂ɑ΂���J�E���g
	int inputUnderCount;
	//�������̏ォ�炻���ʂ蔲���邽�߂̓��͂ɑ΂���J�E���g�̃��Z�b�g�l
	static const int InputUnderCountMax;
	//�����������蔲������s�t���O
	bool doSkeletonThinGround;


	/*
	@fn �W�����v
	*/
	void Jump();
	//�W�����v�{�^���̓��̓t���O
	bool jumpBottonInput;
	//�W�����v�� 
	static const float JumpPower;
	//�W�����v��̕��㒆���@���㒆�̂ݐڐG������s��Ȃ��������邽�ߎg�p
	bool isFloating;
	//ThinGround�I�u�W�F�N�g�ɐڐG���Ă��邩
	bool isThinGroundCollision;
	//�W�����v��i�ڂ����i�ڂ܂ł̃J�E���g
	int doubleJumpInterval;
	//�_�u���W�����v���s�������ǂ���
	bool doubleJump;

	/*
	@fn �d��
	*/
	void Gravity(float _deltaTime);
	//�d��
	static const float GravityPower;

	/*
	@fn ���C
	@brief ���E�����ւ�velocity�֖��C��t�^
	*/
	void Friction(float _friction);
	//���E�����ւ̖��C
	static const float MoveFriction;

	static const float DownFriction;

	/*
	@fn ��e
	@brief HP�����������G���Ԃ�ǉ�����
	*/
	void HitAttack();
	/*
	@fn ���G���Ԃ̊Ǘ�
	*/
	void Invincible();
	//���G��
	bool invincible;
	//���G����
	int invincibleCount;
	//���G���Ԃ̍ő吔
	static const int InvincibleCount;

	static const int HitPointMax;
	int hitPoint;
	static const float HitPointUIWidth;
	static const Vector3 HitPointUIPos;
	static const float HitPointUISize;
	void DrawHitPointUI();
	std::vector<class UserInterfaceBase*> hitPointUI;
	bool isLive;

	int candleHealingInterval;
	static const int CandleHealingInterval;
	void CandleHealingIntervalDown();
};

