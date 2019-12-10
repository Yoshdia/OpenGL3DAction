#pragma once
#include "GameObject.h"
#include "AnimationPlayerComponent.h"

struct InputState;


/*
 @file PlayerCharacter.h
 @brief �v���C���[
	*/
class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState) override;
	void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag = Tag::GroundTag)override;
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	//�A�j���[�V����
	class AnimationPlayerComponent* animationComponent;
	//���̗��A���n���Ă��邩�ǂ��������m����
	class SkeltonObjectChecker* footChecker;

	//���͂ɂ��s������������鎞�ԁ@���AttackPlayerComponent�̍U���A�N�V��������󂯎��
	float canNotActionTime;

	//����
	int direction;

	//�ړ���
	Vector3 velocity;

	/*
	@fn �v���C���[���s���A�N�V����
	*/
	void Actions(float _deltaTime,const bool& _noGround);

	/*
	@fn �U��
	@param _animState �ߐڍU���A�������U���̂ǂ�����s����
	*/
	void Attack(PlayerAnimationState _animState);
	//�ߐڃR���{�A�������U�����s���N���X
	class AttackPlayerComponent* attack;
	//�ߐڍU���{�^���̓��̓t���O
	bool attackBottonInput;
	//�������U���{�^���̓��̓t���O
	bool rangeAttackBottonInput;

	/*
	@fn �h��
	*/
	void Guard();
	//�h��̂��߂̏��̐����A�K�[�h�ς݂̍U���̊Ǘ����s���N���X
	class GuardPlayerComponent* guardComponent;
	//�K�[�h�{�^���̓��̓t���O
	bool guardBottonInput;

	/*
	@fn ���E�ړ�
	@brief ���E�̓��͏������Ƃ�velocity�֒l�������A�j���[�V�������Đ�����
	*/
	void Move(float _deltaTime);
	//���͕����A��...-1 �E...1
	int inputDirection;
	//�ړ����x
	static const float MoveSpeed;

	/*
	@fn �W�����v
	*/
	void Jump();
	//�W�����v�{�^���̓��̓t���O
	bool jumpBottonInput;
	//�W�����v�� 
	static const float JumpPower;

	bool isFloating;


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
	void Friction();
	//���E�����ւ̖��C
	static const float MoveFriction;

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

};

