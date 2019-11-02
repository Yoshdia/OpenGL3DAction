#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "InputSystem.h"
#include "AnimationPlayerComponent.h"
#include "AttackPlayerComponent.h"
#include "ColliderComponent.h"
#include "InputMovePlayerComponent.h"
#include "PhysicsWorld.h"
#include "JumpPlayerComponent.h"
#include "FootSole.h"
#include "GravityComponent.h"

const float PlayerCharacter::jumpPower = 40;

PlayerCharacter::PlayerCharacter() :
	GameObject(),
	movement(Vector3(5, 5, 5)),
	inputDirection(Vector3(0, 0, 0)),
	attackBottonInput(false),
	canNotActionTime(0)
{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);

	tag = Tag::PlayerTag;
	SetPosition(Vector3(0, 0, 0));

	animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerComponent(this, 100);
	std::function<void( ColliderComponent*)>  Enter = std::bind(&PlayerCharacter::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void( ColliderComponent*)>  Stay = std::bind(&PlayerCharacter::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
	inputMovePlayerComponent = new InputMovePlayerComponent(this, 100);
	GravityComponent* gravityComponent = new GravityComponent(this, 100, 20);

	isJump = false;
	new FootSole(position, isJump);
	jumpPlayerComponent = new JumpPlayerComponent(this, 100,jumpPower);
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	if (canNotActionTime < 0)
	{
		if (inputDirection != Vector3::Zero)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Move);
		}
		else
		{
			animationComponent->SetAnimation(PlayerAnimationState::Idle);
		}

		if (attackBottonInput == true)
		{
			canNotActionTime = attack->Attack();
			animationComponent->SetAnimation(PlayerAnimationState::Attack);
		}
	}
	else
	{
		canNotActionTime--;
	}
	SetPosition(position + (inputDirection*movement));
}

void PlayerCharacter::GameObjectInput(const InputState & _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0) == 1)
		printf("\nplayerPosition = {%f,%f,%f}", position.x, position.y, position.z);

	//inputDirection = inputMovePlayerComponent->InputMoveMent(_keyState);
	inputDirection = Vector3::Zero;
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
	{
		inputDirection.x++;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		inputDirection.x--;
	}

	attackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_A);

	if (!isJump)
	{
		if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE))
		{
			isJump = true;
			jumpPlayerComponent->Jump(0);
		}
	}
}

void PlayerCharacter::FixCollision(const AABB & myAABB, const AABB & pairAABB)
{
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void PlayerCharacter::OnTriggerStay(ColliderComponent * colliderPair)
{
}
