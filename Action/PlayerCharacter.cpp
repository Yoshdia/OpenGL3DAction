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

PlayerCharacter::PlayerCharacter() :
	GameObject(),
	movement(Vector3(0, 0, 0)),
	inputDirection(Vector3(0,0,0)),
	attackBottonInput(false),
	canNotActionTime(0)
{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);

	tag = Tag::PlayerTag;
	SetPosition(Vector3(0, 0, 0));

	animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerComponent(this, 100);
	std::function<void(const ColliderComponent*)>  Enter = std::bind(&PlayerCharacter::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(const ColliderComponent*)>  Stay = std::bind(&PlayerCharacter::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(10, 10, 10), myObjectId, Enter, Stay, &movement, tag, Vector3(0, 0, 0));
	inputMovePlayerComponent = new InputMovePlayerComponent(this, 100);
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

		if (attackBottonInput==true)
		{
			canNotActionTime = attack->Attack();
			animationComponent->SetAnimation(PlayerAnimationState::Attack);
		}
	}
	else
	{
		canNotActionTime--;
	}

	SetPosition(position + inputDirection);
}

void PlayerCharacter::GameObjectInput(const InputState & _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0) == 1)
		printf("\nplayerPosition = {%f,%f,%f}", position.x, position.y, position.z);
	inputDirection = inputMovePlayerComponent->InputMoveMent(_keyState);

	attackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE);
}

