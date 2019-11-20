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


const float PlayerCharacter::JumpPower = 25.0f;
const float PlayerCharacter::MoveSpeed = 10.0f;
const float PlayerCharacter::GravityPower = 1.2f;
const float PlayerCharacter::MoveFriction = 1.1f;

PlayerCharacter::PlayerCharacter() :
	GameObject(),
	inputDirection(0),
	canNotActionTime(0),
	velocity(Vector3(0, 0, 0)),
	attackBottonInput(false),
	jumpBottonInput(false),
	rangeAttackBottonInput(false)

{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);

	tag = Tag::PlayerTag;
	SetPosition(Vector3(100, 200, 0));
	float scaleF = 25.0f;
	SetScale(scaleF);

	//animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerComponent(this, 100);

	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	footChecker = new SkeltonObjectChecker(this, Vector3(0, -scaleF, 0), Vector3(20, 1, 20), Tag::GroundTag);

	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	//カメラの追跡先をセット
	RENDERER->SetViewMatrixLerpObject(Vector3(0, 0, -500), position);
	//着地状態
	bool noGround = footChecker->GetNoTouchingFlag();
	//入力によるアクションができるか
	if (canNotActionTime < 0)
	{
		Move();
		//着地しているか
		if (!noGround)
		{
			Jump();
		}
		if (attackBottonInput)
		{
			Attack(PlayerAnimationState::Attack);
		}
		else if (rangeAttackBottonInput)
		{
			Attack(PlayerAnimationState::Range);
		}
	}
	else
	{
		canNotActionTime--;
	}
	//空中なら重力を付与
	if (noGround)
	{
		Gravity();
	}
	Friction();
	SetPosition(position + velocity);
}

void PlayerCharacter::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0) == 1)
		printf("\nplayerPosition = {%f,%f,%f}", position.x, position.y, position.z);

	inputDirection = 0;
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
	{
		inputDirection++;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		inputDirection--;
	}

	attackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_A);
	rangeAttackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_S);
	jumpBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE);

	if (_keyState.Controller.GetIsConnected())
	{
		attackBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B);
		rangeAttackBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A);
		jumpBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y);
	}
}

void PlayerCharacter::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::EnemyTag)
	{
	}
}

void PlayerCharacter::OnTriggerEnter(ColliderComponent * colliderPair)
{
}

void PlayerCharacter::Attack(PlayerAnimationState _animState)
{
	switch (_animState)
	{
	case(PlayerAnimationState::Attack):
		if (attack != nullptr)
		{
			canNotActionTime = attack->Attack();
		}
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Attack);
		}
		break;
	case(PlayerAnimationState::Range):
		if (attack != nullptr)
		{
			canNotActionTime = attack->RangeAttack();
		}
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Range);
		}
		break;
	}
}

void PlayerCharacter::Move()
{
	if (inputDirection != 0)
	{
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Move);
		}
		velocity.x = inputDirection * MoveSpeed;
	}
	else
	{
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Idle);
		}
	}
}

void PlayerCharacter::Jump()
{
	//上下への移動力をリセット
	velocity.y = 0;
	if (jumpBottonInput)
	{
		velocity.y += JumpPower;
	}
}

void PlayerCharacter::Gravity()
{
	velocity.y += -GravityPower;
}

void PlayerCharacter::Friction()
{
	//velocityが一定以下でないなら左右移動へ摩擦を付与
	if (velocity.x >= 0.1f&&velocity.x <= -0.1f)
	{
		velocity.x = 0;
	}
	else
	{
		velocity.x /= MoveFriction;
	}
}
