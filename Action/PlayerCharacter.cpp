#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "InputSystem.h"
#include "AttackPlayerComponent.h"
#include "ColliderComponent.h"
//#include "PhysicsWorld.h"
#include "MeshComponent.h"
#include "SkeltonObjectChecker.h"
#include "GuardPlayerComponent.h"
#include "ParticleComponent.h"
#include "Texture.h"
#include "RotateComponent.h"
//debug
#include "Game.h"
#include "PhysicsWorld.h"
#include "BombParticleEffect.h"
#include "MainCameraObject.h"
#include "GameObjectManager.h"
#include "HeartParticleEffect.h"

const float PlayerCharacter::MoveSpeed = 600;
const float PlayerCharacter::GravityPower = 80;
const float PlayerCharacter::JumpPower = 25.0f;
const float PlayerCharacter::MoveFriction = 1.2f;
const float PlayerCharacter::DownFriction = 1.05f;

const int PlayerCharacter::InvincibleCount = 20;
const int PlayerCharacter::InputUnderCountMax = 30;
const int PlayerCharacter::AvoidanceInterval = 40;
const int PlayerCharacter::AvoidanceInvincible = 30;
const int PlayerCharacter::CandleHealingInterval = 200;

PlayerCharacter::PlayerCharacter(const Vector3& _pos) :
	GameObject(),
	inputDirection(0),
	canNotActionTime(0),
	velocity(Vector3(0, 0, 0)),
	attackBottonInput(false),
	jumpBottonInput(false),
	rangeAttackBottonInput(false),
	avoidanceBottonInput(false),
	direction(1),
	invincible(false),
	invincibleCount(0),
	isFloating(false),
	isThinGroundCollision(false),
	noInputForUnderDirection(false),
	doSkeletonThinGround(false),
	isLive(true),
	hitPoint(10),
	avoidancing(false),
	avoidanceInterval(0),
	candleHealingInterval(0)
{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);

	tag = Tag::PlayerTag;
	//SetPosition(Vector3(00, 200, 0));
	SetPosition(_pos);
	float scaleF = 60.0f;
	SetScale(scaleF);

	animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerComponent(this, 100);
	//guardComponent = new GuardPlayerComponent(this, 100);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	footChecker = new SkeltonObjectChecker(this, Vector3(0, -30, 0), Vector3(20, 1, 20), Tag::GroundTag);
	thinChecker = new SkeltonObjectChecker(this, Vector3(0, -30, 0), Vector3(20, 1, 20), Tag::ThinGroundFloor);
	headRoofChecker = new SkeltonObjectChecker(this, Vector3(0, 30, 0), Vector3(20, 1, 20), Tag::GroundTag);

	RotateComponent* rota = new RotateComponent(this);
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	isThinGroundCollision = false;
	//�J�����̒ǐՐ���Z�b�g
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 0, -500), position);
	//���n���
	bool noGround = footChecker->GetNoTouchingFlag() && (thinChecker->GetNoTouchingFlag());

	//���n��Ԃ̂Ƃ��㉺�����ւ̗͂����Z�b�g����
	if ((!noGround && !isFloating) || !headRoofChecker->GetNoTouchingFlag())
	{
		velocity.y = 0;
	}
	//���͂ɂ��A�N�V�������ł��邩
	if (canNotActionTime < 0 && !invincible)
	{
		Actions(_deltaTime, noGround);
	}
	else
	{
		canNotActionTime--;
	}
	//�󒆂Ȃ�d�͂�t�^
	if (noGround || (doSkeletonThinGround/*&& !noGround*/))
	{
		Gravity(_deltaTime);
		if (inputUnderDirection > 0)
		{
			doSkeletonThinGround = true;
		}
		if (velocity.y < 0)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Drop);
		}
		else
		{
			animationComponent->SetAnimation(PlayerAnimationState::Jump);
		}
	}
	if (avoidancing)
	{
		animationComponent->SetAnimation(PlayerAnimationState::Guard);
	}
	//�W�����v�ɂ�蕂�㒆��
	if (velocity.y <= 0)
	{
		isFloating = false;
	}
	else
	{
		isFloating = true;
	}
	CandleHealingIntervalDown();
	Friction(MoveFriction);
	AcoidanceIntervalDown();
	SetPosition(position + (velocity));
	Invincible();
	SkeletonThinGround();
}

void PlayerCharacter::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0) == 1)
		printf("\nplayerPosition = {%f,%f,%f}", position.x, position.y, position.z);

	if (!avoidancing)
	{
		inputDirection = 0;
	}
	inputUnderDirection = false;

	//�R���g���[���[���ڑ����ꂽ�ꍇ������R���g���[���[�ɕύX
	if (InputSystem::GetConnectedController())
	{
		attackBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X);
		rangeAttackBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y);
		avoidanceBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B);
		jumpBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A);
		inputDirection = _keyState.Controller.GetLAxisVec().x;
	}
	else
	{
		if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
		{
			inputDirection = 1;
		}
		if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
		{
			inputDirection = -1;
		}
		if (inputDirection == 0 && avoidancing)
		{
			inputDirection = direction;
		}
		//if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_DOWN))
		//{
		//	inputUnderDirection = true;
		//}
		inputUnderDirection = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN);

		attackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_A);
		rangeAttackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_S);
		avoidanceBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_D);
		jumpBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE);
	}
	//�OF�Ɠ��͖@���Ⴂ�A�X�e�B�b�N�̓��͂�0�łȂ��ꍇ�v���C���[�̌������X�V
	if (direction != inputDirection && inputDirection != 0)
	{
		direction = inputDirection;
	}

	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_3))
	{
		Game::debug = 0;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_4))
	{
		Game::debug = 1;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_5))
	{
		//new BombParticleEffect(position, Vector3(10, 16, 0),true);
		//new BombParticleEffect(position, Vector3(10, 12, 0),true);
		//new BombParticleEffect(position, Vector3(10, 9, 0),true);
		//new BombParticleEffect(position, Vector3(10, 6, 0),true);
		//new BombParticleEffect(position, Vector3(10, 3, 0),true);
		//new BombParticleEffect(position, Vector3(-10, 16, 0),true);
		//new BombParticleEffect(position, Vector3(-10, 12, 0),true);
		//new BombParticleEffect(position, Vector3(-10, 9, 0),true);
		//new BombParticleEffect(position, Vector3(-10, 6, 0),true);
		//new BombParticleEffect(position, Vector3(-10, 3, 0),true);
		new HeartParticleEffect(position, Vector3(15, 2.5, 0));
		new HeartParticleEffect(position, Vector3(-15, 2.5, 0));
		new HeartParticleEffect(position, Vector3(5, 2.5, 0));
	}
}

void PlayerCharacter::FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag & _pairTag)
{
	//���㒆�ł��������ɂ��łɐڐG���Ă���ꍇ�͂߂肱�ݕ␳���s��Ȃ�
	if (_pairTag == Tag::ThinGroundFloor)
	{
		if ((isFloating && isThinGroundCollision) || doSkeletonThinGround)
		{
			return;
		}
	}
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void PlayerCharacter::PausingUpdateGameObject()
{
	if (pauzingEvent == PauzingEvent::DeadPlayerEvent)
	{
		velocity.y = -1;
		SetPosition(position + velocity);
		Friction(DownFriction);
		animationComponent->SetAnimation(PlayerAnimationState::Down);
	}
}

bool PlayerCharacter::GetGameEnd()
{
	if (hitPoint <= 0)
	{
		return true;
	}
	return false;
}

void PlayerCharacter::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::ThinGroundFloor)
	{
		isThinGroundCollision = true;
		return;
	}
	if (colliderPair->GetObjectTag() == Tag::CandleStickTag)
	{
		if (candleHealingInterval < 0)
		{
			hitPoint++;
			printf("heal");
			candleHealingInterval = 100;
		}
		return;
	}
}

void PlayerCharacter::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::EnemyWeaponTag)
	{
		if (!invincible && !avoidancing)
		{
			//�Փ˂����G�̍U�����A�h��ς݂łȂ���
			//if (!guardComponent->SearchObjectId(colliderPair->GetId()))
			//{
				//�v���C���[�̍U���̕������v�Z��nockBackForce�Ɍv�Z
			double distance = Math::Sqrt((colliderPair->GetPosition().x - position.x) * (colliderPair->GetPosition().x - position.x) + (colliderPair->GetPosition().y - position.y) * (colliderPair->GetPosition().y - position.y));
			Vector3 force = Vector3::Normalize(Vector3((position.x - colliderPair->GetPosition().x), 0, (position.z - colliderPair->GetPosition().z)));
			velocity.x = force.x * 10;
			animationComponent->SetAnimation(PlayerAnimationState::Outi);
			HitAttack();
			//}
		}
	}
}

void PlayerCharacter::Actions(float _deltaTime, const bool& _noGround)
{
	bool actioned = false;
	if (attackBottonInput && !avoidancing)
	{
		Attack(PlayerAnimationState::Attack);
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Attack);
		}
		actioned = true;
	}
	else if (rangeAttackBottonInput && !avoidancing)
	{
		Attack(PlayerAnimationState::Range);
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Range);
		}
		actioned = true;
	}
	else
	{
		//Guard();
		Avoidance();
		if (inputDirection != 0 || avoidancing)
		{
			Move(_deltaTime);
			actioned = true;
		}

		//���n���Ă��邩
		if (!_noGround)
		{
			if (jumpBottonInput)
			{
				Jump();
				actioned = true;
			}
			//animationComponent->SetAnimation();
		}
		//�������ւ̓��͂����邩
		if (inputUnderDirection > 0)
		{
			//�������̂��蔲���\�Ȏ��Ԃ̃f�B���C���Z�b�g
			inputUnderCount = InputUnderCountMax;
		}
	}
	if (!actioned)
	{
		if (velocity.y == 0)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Idle);
		}
	}
}

void PlayerCharacter::Attack(PlayerAnimationState _animState)
{
	switch (_animState)
	{
	case(PlayerAnimationState::Attack):
		if (attack != nullptr)
		{
			canNotActionTime = attack->Attack(direction);
		}
		break;
	case(PlayerAnimationState::Range):
		if (attack != nullptr)
		{
			canNotActionTime = attack->RangeAttack(direction);
		}
		break;
	}
}

//void PlayerCharacter::Guard()
//{
	//canNotActionTime = guardComponent->Guard();
//}

void PlayerCharacter::Avoidance()
{
	if (avoidanceBottonInput)
	{
		if (avoidanceInterval <= 0)
		{
			avoidancing = true;
			animationComponent->SetAnimation(PlayerAnimationState::Guard);
			avoidanceInterval = AvoidanceInterval;
			invincibleCount = AvoidanceInvincible;
		}
	}
}

void PlayerCharacter::AcoidanceIntervalDown()
{
	if (avoidanceInterval <= 0)
	{

	}
	else
	{
		avoidanceInterval--;
	}
}

void PlayerCharacter::Move(float _deltaTime)
{
	if (inputDirection != 0)
	{
		if (animationComponent != nullptr&&velocity.y == 0)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Move);
		}
		velocity.x = (MoveSpeed * _deltaTime) * inputDirection;
	}
	else
	{
		//if (animationComponent != nullptr)
		//{
		//	animationComponent->SetAnimation(PlayerAnimationState::Idle);
		//}
	}
}

void PlayerCharacter::SkeletonThinGround()
{
	//�������ւ̓��͂���������ق��ɕω����Ȃ��J�E���g���߂����ꍇ���ׂă��Z�b�g����
	if (inputUnderCount <= 0)
	{
		inputUnderCount = 0;
		noInputForUnderDirection = false;
		doSkeletonThinGround = false;
	}
	else
	{
		inputUnderCount--;
		//�������ւ̓��͂�����������1�����̉������ւ̓���(�j���[�g����)���������ꍇ
		if (inputUnderDirection < 1)
		{
			noInputForUnderDirection = true;
		}
	}
	//�������ւ̓��͂����肻�̒���j���[�g�����ɂ��铙�̑��삪�������炷�蔲�������s
	if (noInputForUnderDirection&&inputUnderDirection > 0)
	{
		inputUnderCount = 0;
		noInputForUnderDirection = false;
		doSkeletonThinGround = true;
	}
}

void PlayerCharacter::Jump()
{
	//�㉺�ւ̈ړ��͂����Z�b�g
	//if (!isThinGroundCollision)
	{
	}
	if (velocity.y <= 0)
	{
		velocity.y += JumpPower;
	}
	else
	{

	}

}

void PlayerCharacter::Gravity(float _deltaTime)
{
	velocity.y += -GravityPower * _deltaTime;

	if (velocity.y <= -25)
	{
		velocity.y = -25;
	}
}

void PlayerCharacter::Friction(float _fricton)
{
	//velocity�����ȉ��łȂ��Ȃ獶�E�ړ��֖��C��t�^
	if (velocity.x >= 0.1f && velocity.x <= -0.1f)
	{
		velocity.x = 0;
	}
	else
	{
		velocity.x /= _fricton;
	}
}

void PlayerCharacter::HitAttack()
{
	invincibleCount = InvincibleCount;
	invincible = true;
	new HeartParticleEffect(position, Vector3(15, 2.5, 0));
	new HeartParticleEffect(position, Vector3(-15, 2.5, 0));
	new HeartParticleEffect(position, Vector3(5, 2.5, 0));
	if (hitPoint <= 0)
	{
		isLive = false;
		pauzingEvent = PauzingEvent::DeadPlayerEvent;
	}
	else
	{
		hitPoint--;
	}
}

void PlayerCharacter::Invincible()
{
	if (invincibleCount <= 0)
	{
		invincible = false;
		avoidancing = false;
	}
	else
	{
		invincibleCount--;
	}
}

void PlayerCharacter::CandleHealingIntervalDown()
{
	if (candleHealingInterval >= 0)
	{
		candleHealingInterval--;
	}
}
